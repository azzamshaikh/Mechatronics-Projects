//  ME 497.007
//  Lab 1: Morse Code
//  Jarret Jack and Azzam Shaikh
//  January 22, 2019

//  Code for transmitting Arduino 

//  Declare variables
int led = 12;           //  Set pin that LED is on
int val_12 = 0;         //  Initialize a variable that will store the value 
                        //      returned reading from pin 12 [transmitting Arduino output]
int val_5 = 0;          //  Initialize a variable that will store the value 
                        //      returned reading from pin 5 [receiving Arduinos output]
int counter = 0;        //  Initialize a variable that will be used in the error_counter 
                        //      function as the counter


void setup() {
  pinMode(12, OUTPUT);  //  Set pin 12 as an output
  pinMode(5,INPUT);     //  Set pin 5 as the input
  Serial.begin(9600);   //  Initialize serial communication
}

void loop() { 
  // Follow International Morse code to transmit a 4 letter word (EXIT)

  //  Morse code for E
  dot();                //  Call dot function to output to the LED
  space();              //  Place a space after the letter
  Serial.print('E');    //  Print out the letter E to the serial monitor

  // Morse code for X
  dash();               //  Call dash function to output to the LED
  dot();                //  Call dot function to output to the LED
  dot();                //  Call dot function to output to the LED
  dash();               //  Call dash function to output to the LED
  space();              //  Place a space after the letter
  Serial.print('X');    //  Print out the letter X to the serial monitor

  // Morse code for I 
  dot();                //  Call dot function to output to the LED
  dot();                //  Call dot function to output to the LED
  space();              //  Place a space after the letter
  Serial.print('I');    //  Print out the letter I to the serial monitor
  
  // Morse code for T
  dash();               //  Call dash function to output to the LED
  space();              //  Place a space after the letter
  Serial.print('T');    //  Print out the letter T to the serial monitor
  
  Serial.println();     //  Print a new line after finishing the word
}

void dot() {
  // Function to create the dot in Morse code
  digitalWrite(led, HIGH);  //  Set the led pin on
  delay(500);               //  Add a 500 ms delay to be distinguished as a dot 
  error_counter();          //  Run error_counter function to add to the error counter
  digitalWrite(led, LOW);   //  Set the led pin off
  delay(1000);              //  Add a 1000 ms delay to be distingushed as the end 
                            //      [space will be added to further distingish the end of the letter]
  error_counter();          //  Run error_counter function to add to the error counter
}

void dash() {
  // Function to create the dash in Morse code
  digitalWrite(led, HIGH);  //  Set the led pin on
  delay(1000);              //  Add a 1000 ms delay to be distinguished as a dash
  error_counter();          //  Run error_counter function to add to the error counter
  digitalWrite(led, LOW);   //  Set the led pin off
  delay(1000);              //  Add a 1000 ms delay to be distingushed as the end 
                            //      [space will be added to further distingish the end of the letter]
  error_counter();          //  Run error_counter function to add to the error counter
}

void space() {
  // Function to add a space between letters
  digitalWrite(led, LOW);   //  Set the led pin off
  delay(1000);              //  Add an additional 1000 ms delay to further distinguish the end of the letter
  error_counter();          //  Run error_counter function to add to the error counter
}

void error_counter() {
  // Create a function that will count the amount of errors that are detected during run-time
  
  // This function will compare the the output from pin 12 (transmitting Arduino) and the input from pin 5 (output of the receiving Arduino)
  val_5 = digitalRead(5);                   //  Use the digitalRead function to import the value from pin 5
  val_12 = digitalRead(12);                 //  Use the digitalRead function to import the value from pin 12

 if(val_5 == HIGH && val_12 == LOW){        //  Error Case 1: transmitter (val_5) is on and receiver (val_12) is off
                                            //      If the case 1 condition is met, the if statement will be entered
    counter = counter + 1;                  //  Add 1 to the counter everytime error case 1 is met
    Serial.println("Case 1");               //  Print the error case that was met
    }
  else if(val_5 == LOW && val_12 == HIGH){  //  Error Case 2: trasmitter (val_5) is off and receiver (val_12) is on
                                            //      If this case 2 condition is met, the if statement will be entered
    counter = counter + 1;                  //  Add 1 to the counter everytime error case 2 is met
    Serial.println("Case 2");               //  Print the error case that was met
  }
  if(counter > 0){                          //  Use an if statement to only print when there are more than 0 errors 
    Serial.print("ERROR number ");          //  Print the initial phrase to the serial monitor
    Serial.println(counter);                //  Print the counter variable using the println in order to create a new line after the number is printed
  }
}

// End of code
