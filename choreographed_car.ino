/*
  SparkFun Inventor’s Kit
  Circuit 3A-Servo

  Move a servo attached to pin 9 so that it's angle matches a potentiometer attached to A0.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <Servo.h>          //include the servo library

int potPosition;           //this variable will store the position of the potentiometer
int servoPosition;         //the servo will move to this position

Servo myservo;              //create a servo object

//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//VARIABLES
int motorSpeed = 0;       //starting speed for the motor

//TIMER VARIABLES
bool delayRunning = false;
int delayStart = 0;

//STEP VARIABLE
int currentStep = 0;

void setup() {
  Serial.begin (9600);
  myservo.attach(9);        //tell the servo object that its servo is plugged into pin 9

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  delayRunning = true; // not finished yet
  delayStart = millis();

}

void loop() {

  //STEP START
  // check if delay has timed out after 10sec == 10000mS
  if (currentStep == 0 && ((millis() - delayStart) >= 1000)) {
    //delayRunning = false; // // prevent this code being run more then once
    myservo.write(95);
    spinMotor(0);
    Serial.println("STEP START COMPLETED");
    currentStep = 1;
  }

  //STEP ONE
  // check if delay has timed out after 10sec == 10000mS
  if (currentStep == 1 && ((millis() - delayStart) >= 4000)) {
    //delayRunning = false; // // prevent this code being run more then once
    spinMotor(150);
    Serial.println("STEP ONE FINISHED");
    currentStep = 2;
  }

  //STEP TWO
  if (currentStep == 2 && ((millis() - delayStart) >= 8000)) {
    //delayRunning = false; // // prevent this code being run more then once
    spinMotor(0);
    myservo.write(120);
    Serial.println("STEP TWO FINISHED");
    currentStep = 3;
  }

  //STEP THREE
  if (currentStep == 3 && ((millis() - delayStart) >= 10000)) {
    spinMotor(-150);
    //delayRunning = false; // // prevent this code being run more then once
    Serial.println("STEP THREE FINISHED");
    currentStep = 4;
  }

  //STEP FOUR
  if (currentStep == 4 && ((millis() - delayStart) >= 15000)) {
    spinMotor(0);
    myservo.write(70);
    //delayRunning = false; // // prevent this code being run more then once
    Serial.println("STEP FOUR FINISHED");
    currentStep = 5;
  }

  //STEP FIVE
  if (currentStep == 5 && ((millis() - delayStart) >= 17000)) {
    spinMotor(150);
    //delayRunning = false; // // prevent this code being run more then once
    Serial.println("STEP FIVE FINISHED");
    currentStep = 6;
  }

  //STEP STOP
  if (currentStep == 6 && ((millis() - delayStart) >= 23000)) {
    spinMotor(0);
    myservo.write(95);
    delayRunning = false; // // prevent this code being run more then once
    Serial.println("STEP STOP FINISHED");
    currentStep = 99;
  }

  // if (Serial.available() > 0) {         //if the user has entered something in the serial monitor
  //   motorSpeed = Serial.parseInt();     //set the motor speed equal to the number in the serial message. Max +-255

  //   Serial.print("Motor Speed: ");      //print the speed that the motor is set to run at
  //   Serial.println(motorSpeed);
  // }

  // spinMotor(motorSpeed);

  //potPosition = analogRead(A0);                     //use analog read to measure the position of the potentiometer (0-1023)

  // potPosition = 30;
  // servoPosition = map(potPosition, 0, 1023, 20, 160); //convert the potentiometer number to a servo position from 20-160
  //                                                     //Note: its best to avoid driving the little SIK servos all the
  //                                                     //way to 0 or 180 degrees it can cause the motor to jitter, which is bad for the servo.

  // //Serial.print(servoPosition);     //print the distance that was measured
  // Serial.print("servoPos: ");
  // Serial.println(servoPosition);      //print units after the distance (48-118 range for car)                                                   

  // myservo.write(servoPosition);                      //move the servo to the 10 degree position
  // Serial.println("delay");
  delay(2000);
}

/********************************************************************************/
void spinMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
