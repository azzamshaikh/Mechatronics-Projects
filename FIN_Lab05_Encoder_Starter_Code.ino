// Initialize variables 
const int ch_A = 2;     //  Pin for channel A
const int ch_B = 3;     //  Pin for channel B
int t0 = 0;             //  Initialize timer 0 
int t1 = 0;             //  Initialize timer 1

//  Volatile variables which change inside and outside of the interrupt service routine
volatile int encoder_count = 0;           // Variable to store the encoder position
volatile boolean changeFlagA = false;     // Variable used to check if encoder has moved

void setup() {
  //Setup channel A as an interrupt pin with a specified mode: RISING,FALLING,CHANGE
  pinMode(ch_A,INPUT);          //  Initialize pin for channel A as an input
  //attachInterrupt(digitalPinToInterrupt(ch_A), interrupt_A, RISING);      //  Create an interrupt routine for channel A when the signal is rising (low to high)
  //attachInterrupt(digitalPinToInterrupt(ch_A), interrupt_A, FALLING);     //  Create an interrupt routine for channel A when the signal is falling (high to low)
  attachInterrupt(digitalPinToInterrupt(ch_A), interrupt_A, CHANGE);        //  Create an interrupt routine for channel A when the signal is changing (high to low and vice versa)
  
  pinMode(ch_B,INPUT);          //  Initialize pin for channel B as an input
  //attachInterrupt(digitalPinToInterrupt(ch_B), interrupt_B, CHANGE);      //  Create an interrupt routine for channel B when the signal is changing (high to low and vice versa)

  pinMode(LED_BUILTIN, OUTPUT); //  Initialize output LED
  Serial.begin(115200);         //  Initialize serial baud rate
  t0 = micros();                //  Begin timer 0
  
  //---------**The following for loop will needs to run with all interrupt routines commented out**----------
  //  Purpose is to see how long it takes for the Arduino to run the code for a VERY long time
  for(int x = 0; x <= 25000;x++){                           //  Run the 25000 times
    if (digitalRead(ch_B) == HIGH) {                        //  Look for a low-to-high on channel B
      if (digitalRead(ch_A) == HIGH) {                      //  Check channel A to see which way encoder is turning
        encoder_count--;                                    //  CCW
      }
      else {
        encoder_count++;                                    //  CW
      }
    }
  else {                                                    //  Look for a high-to-low on channel B
      if (digitalRead(ch_A) == LOW) {                       //  Check channel B to see which way encoder is turning
        encoder_count--;                                    //  CCW
      }
      else {
        encoder_count++;                                    //  CW
      }
    }
  }
  t1 = micros();                                            //  Start timer 1
  Serial.println(t1-t0);                                    //  Printout time it takes to run 25000 cycles of the code
}

void loop() {
  // The following if statement prevents the serial monitor from continuously printing.  
  if (changeFlagA)                    // Checks for FlagA to be TRUE
  //  Meaning their has been an interrupt, i.e. encoder has moved.
  {
    changeFlagA = false;              //  Changes the flag back to false
    Serial.println(encoder_count);    //  Prints only when the shaft is rotated.
  }  
}

// The interrupt service routine for Channel A
void interrupt_A()
{
  //  Due to a CHANGE interrupt routine, a low to high and high to low signal change needs to be checked for
  if (digitalRead(ch_A) == HIGH) {          //  Check for a low to high signal change on channel A
    if (digitalRead(ch_B) == LOW) {         //  Check channel B's signal to see which way encoder is turning
      encoder_count--;                      //  CCW
    }
    else {
      encoder_count++;                      //  CW
    }
  }
  else                                      //  Check for a high to low signal change on channel A
  {
    if (digitalRead(ch_B) == HIGH) {        //  Check channel B's signal to see which way encoder is turning
      encoder_count--;                      //  CCW
    }
    else {
      encoder_count++;                      //  CW
    }
  }
  changeFlagA = true;                       //  Sets FlagA to true when the encoder is rotated
}

// The interrupt service routine for Channel B
void interrupt_B()
{
  //  Due to a CHANGE interrupt routine, a low to high and high to low signal change needs to be checked for
  if (digitalRead(ch_B) == HIGH) {        //  Check for a low to high signal change on channel B
    if (digitalRead(ch_A) == HIGH) {      //  Check channel A's signal to see which way encoder is turning
      encoder_count--;                    //  CCW
    }
    else {
      encoder_count++;                    //  CW
    }
  }
  else {                                  //  Check for a high to low signal change on channel B
    if (digitalRead(ch_A) == LOW) {       //  Check channel B's signal to see which way encoder is turning
      encoder_count--;                    //  CCW
    }
    else {
      encoder_count++;                    //  CW
    }
  }
}

//  End of code
