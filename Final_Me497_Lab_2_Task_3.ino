// ME 497 -- 007 
// Lab 02 -- TTL logic chips 
// Jarrett John and Azzam Shaikh
// January 29, 2019

// Master Arduino Task 3

//  Declare Variables
const byte ledPin = 13;               //  Variable referencing pin for LED
const byte loopbackPin = 2;           //  Variable referencing pin for loopback
const byte ttlPin = 3;                //  Variable referencing pin for TTL 
volatile byte state = LOW;            //  Variable referencing state initialized to LOW
volatile long t0;                     //  Variable for timer zero
volatile long t1;                     //  Variable for timer one
volatile long t2;                     //  Variable for time two
volatile long dt1;                    //  Variable for time difference one
volatile long dt2;                    //  Variable for time difference two

void setup() {
  //  Initalize pin modes, call attach interrupt function, initalize serial communication
  pinMode(ledPin, OUTPUT);                //  Set led pin as an output
  pinMode(loopbackPin, INPUT_PULLUP);     //  Set loopback pin as input
  pinMode(ttlPin, INPUT_PULLUP);          //  Set TTL pin as input
  attachInterrupt(digitalPinToInterrupt(loopbackPin), loopBack, CHANGE);    //  Call interrupt function on the loopback pin upon singal change and call loopBack function
  attachInterrupt(digitalPinToInterrupt(ttlPin), loopBackTTL, CHANGE);      //  Call interrupt fnction on the TTL pin upon singal change and call loopBackTTL function
  Serial.begin(115200);     //  Initalize serial communication at a baud rate of 115200
}

void loop() {
  //  Create function that will be looped 
  t0 = micros();                   // Start the timer
  digitalWrite(ledPin, state);     // Set the LED state
  delay(250);                      // Wait to allow the logical operation to give a response
  state = !state;                  // Change the state variable so LED will change state on next loop
  dt1 = t1 - t0;                   // Time between setting the LED state and detecting it on interrupt
  dt2 = t2 - t1;                   // Time between detecting TTL loopback signal change and loopBack signal change
 
  Serial.print("Loopback (micro secs): ");  //  Print loopback data to serial monitor
  Serial.println(dt1);                      //  Print loopback data to serial monitor  
  
  Serial.print("Loopback for TTL Chip (micro secs): ");    // Print TTL loopback data to serial monitor
  Serial.println(dt2);                                     // Print TTL loopback data to serial monitor
  
  
  byte loopPin = digitalRead(loopbackPin);      // Detect the current state of the LED
  byte ttlPin = digitalRead(ttlPin);            // Detect the current state of the ttlPin 
  byte expect = loopPin ^ ttlPin;               // Perform the logical operation of the TTL chip [SN74HC86N: XOR]
  // Create logic conditions to check if TTL and loopPins create the correct expected value
  if(loopPin == ttlPin && expect == 0){         //  If the loopPin and ttlPin are equal [(0 & 0) or (1 & 1)] and expect is equal to 0:
    Serial.println("Correct!");                 //  Print that the TTL and loopPins output the correct value
  }
  else  if(loopPin != ttlPin && expect == 1){   //  If the loopPin and ttlPin are not equal [(0 & 1) or (1 & 0)] and expect is equal to 1:
    Serial.println("Correct!");                 //  Print that the TTL and loopPins output the correct value
  }
  else{                                         //  If none of these conditions are met:
    Serial.println("Error!");                   //  Print that an error has occurred
  }
  delay(250);                                   //  Wait to allow the logical operation to give a response

}

void loopBack() {
  // This function is excecuted every time the signal on 'loopbackPin' changes.
  t1 = micros();        // Get the loopback time (micro secs)
}

void loopBackTTL () {
  // This function is exectued every time the TTL's output signal changes value
  t2 = micros();        // Get the loopback time for the TTL output (mirco secs)  
}

// End of code
