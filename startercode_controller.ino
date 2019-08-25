//  RedBot Controller Code

//  Call RedBot library
#include <RedBot.h>

//  Create RedBotSensor objects for reading potentiometers
RedBotSensor lMotor = RedBotSensor(4);
RedBotSensor rMotor = RedBotSensor(1);

void setup() {
  Serial.begin(9600);       //  Initiate serial communication for transmitting data to recieving XBee
}

void loop() { 
  int lMotorRead = lMotor.read();       //  Read signal from left potentiometer on controller
  int rMotorRead = rMotor.read();       //  Read signal from right potentiometer on controller
  int lValue = map(lMotorRead, 0, 1023, -255, 255);   //  Map the left potentiometer signal within the boundary for the motor input values
  int rValue = map(rMotorRead, 0, 1023, 510, 1020);   //  Map the right potentiometer to a certain range so it can be distinguishable for the recieving code
  Serial.println(lValue);               //  Print out the left signal reading on a new line
  Serial.println(rValue);               //  Print out the right signal reading on a new line
}

//  End of code
