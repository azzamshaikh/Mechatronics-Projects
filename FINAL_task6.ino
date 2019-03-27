//  Declare Variables
int sensorPin = A0;     //  Declare variable for sensor pin 
int sensorInitial;      //  Initalize variable for initial sensor reading 
int filterPin = A2;     //  Declare variable for filter pin
int counter = 0;        //  Initialize variable for counter

int t0;                 //  Initalize variable for timer

// Initalize variables used in linear difference equation
float a0 = 1.0000;      //  Coefficient A0
float a1 = -1.7786;     //  Coefficient A1
float a2 = 0.8008;      //  Coefficient A2
float b0 = 0.0055;      //  Coefficient B0
float b1 = 0.0111;      //  Coefficient B1
float b2 = 0.0055;      //  Coefficient B2
float u0;               //  Input variable
float u1 = 0;           //  Input initial value
float u2 = 0;           //  Input initial value
float y;                //  Output variable
float y1 = 0;           //  Output initial value
float y2 = 0;           //  Output initial value
  
void setup() {
  Serial.begin(9600);                     //  Initialize serial monitor
  pinMode(sensorPin, INPUT);              //  Initialize serial pin
  pinMode(filterPin, INPUT);              //  Initialize filter pin
  sensorInitial = analogRead(sensorPin);  //  Store inital sensor reading
}

void loop() {
  t0 = millis();                          //  Begin timer
  sensorValue = analogRead(sensorPin);    //  Read sensor reading
  float sensorVoltage = sensorValue*(5.0/1023.0);   //  Convert sensor reading to volts

  filterValue = analogRead(filterPin);    //  Read filter reading
  float filterVoltage = filterValue*(5.0/1023.0);   //  Convert filter reading to volts
    
  if(t0 % 10 == 0){                       //  Output data in 10 ms intervals [100 Hz]
    if(199 < counter){                    //  Allow only 200 data points to be outputted
                                          //    Does nothing
    }
    else{                                 //  Data outputted to serial monitor
        u0 = sensorVoltage;               //  Store u0 as sensor voltage
        y = (1/a0)*(b0*u0 + b1*u1 + b2*u2 - a1*y1 - a2*y2);     //  Use simple linear difference equation for 2nd order filter
        Serial.print(sensorVoltage);      //  Print out sensor voltage
        Serial.print("\t");               //  Create a tab
        Serial.print(filterVoltage);      //  Print out filter voltage
        Serial.print("\t");               //  Create a tab
        Serial.print(y);                  //  Print out digital filter voltage
        Serial.print("\t");               //  Create a tab
        Serial.println(t0);               //  Print out time
        u2 = u1;                          //  Store u2 value as u1
        u1 = u0;                          //  Store u1 value as u0
        y2 = y1;                          //  Store y2 value as y1
        y1 = y;                           //  Store y1 value as y
        counter++;                        //  Add to counter
    }
  }
}

// End of code
