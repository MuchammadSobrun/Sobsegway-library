/*
 * Bismillahirohmanirrohim
  sobsegway.ino - Program for control BLDC Motor.
  Created by Muchammad Sobrun Ibnu Atfal, December 21, 2017.
  Released into the private domain.
  Research and Developtment.
  CT Asia Robotics Co.ltd.
  Copyright 2017
  all rights reserved
*/

#include "sobsegway.h"
#include "Arduino.h"
#include <PS2X_lib.h>

#define PS2_DAT       17  //14    
#define PS2_CMD       16  //15
#define PS2_SEL       15  //16
#define PS2_CLK       14  //17
#define LED2          52

#define pressures   false
#define rumble      false

// insert your motor name variable here
motor motor;


PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

String ID_motor;
String Str1;
unsigned long time;
char inData[4];
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  pinMode(LED2,OUTPUT);
// insert your pin initialization here (Speed left motor, Direction left motor1,Speed right motor,int dir2)
  motor.init(12,11,53,10,9,8,7,5,6,4,2,3);

  Serial.begin(57600);
   //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
   // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void test_joystick()
{
 
  ps2x.read_gamepad(); //This needs to be called at least once a second
                     // to get data from the controller.
                           
   if (ps2x.Button(PSB_PAD_DOWN)){
      Serial.println("BACKWARD");
      motor.sobsegway(-10, 10,-10,10);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }  

   else if (ps2x.Button(PSB_PAD_UP)){
      Serial.println("FORWARD ");
      motor.sobsegway(10, -10,10,-10);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

   else if (ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("left ");
      motor.sobsegway(-20, -20,-20,-20);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

   else if (ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("right ");
      motor.sobsegway(20,20,20,20);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

   else if (ps2x.Button(PSB_CIRCLE)){
      Serial.println("Circle ");
      motor.sobsegway(40,40,40,40);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

   else if (ps2x.Button(PSB_SQUARE)){
      Serial.println("Square ");
      motor.sobsegway(-40,-40,-40,-40);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

   else if (ps2x.Button(PSB_TRIANGLE)){
      Serial.println("Triangle ");
      motor.sobsegway(50,-50,50,-50);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

   else if (ps2x.Button(PSB_CROSS)){
      Serial.println("Cross ");
      motor.sobsegway(-50,50,-50,50);
      digitalWrite(LED2,HIGH);
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

  else if(ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY)); 
      Serial.print(" , ");
      int data_speed_raw = ps2x.Analog(PSS_LY);
      int data_speed_map = map(data_speed_raw,127,0,0,70);
      Serial.println(data_speed_map);
      motor.sobsegway(data_speed_map, data_speed_map*-1,data_speed_map,data_speed_map*-1);
    } 

   else
    {
    time = millis();
    if(time <= 10)
    {
    //motor.sobsegway(5,-5,5,-5);
    motor.sobsegway(0,0,0,0);
    motor.stoped();
    }
    
    else if(time >11)
    {
    //motor.sobsegway(3,-3,3,-3);
    motor.stoped();
    }
    digitalWrite(LED2,LOW);}
    delay(50);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }}

void Command_serial()
{
  //Serial.available();
if (stringComplete) {
 // Serial.println(inputString);

char a = Serial.read();

String ID = inputString.substring(0,1);
int ID_int = ID.toInt();

if(ID_int >= 1 && ID_int <= 4){
  Serial.println("OK");
if(ID_int >-1){
  Serial.print("ID : ");
  Serial.println(ID_int);
  Serial.print("Data : ");
  Serial.println(inputString.substring(1,3));
}
if (inputString.substring(1,3) == "EN"){
  motor.enable();
  Serial.println("ENABLE ");
  Serial.println(" ");
}
else if (inputString.substring(1,3) == "DI"){
  motor.disable();
  Serial.println("DISABLE ");
  Serial.println(" ");
}}

else if (inputString.substring(0,7) == "FORWARD"){
  Serial.println("FORWARD");
  String ID = inputString.substring(8,10);
  String speedM = inputString.substring(10,15);
  int speedMotor = speedM.toInt();
  motor.sobsegway(speedMotor, speedMotor*-1,speedMotor,speedMotor*-1);
  Serial.print("ID: ");
  Serial.println(ID);
  Serial.print("Speed: ");
  Serial.println(speedMotor);
  Serial.println(" ");
  if (speedMotor>0){
    digitalWrite(LED2,HIGH);}
  else{
    digitalWrite(LED2,LOW);}
}

else if (inputString.substring(0,7) == "REVERSE"){
  Serial.println("REVERSE");
  String ID = inputString.substring(8,10);
  String speedM = inputString.substring(10,15);
  int speedMotor = speedM.toInt();
  motor.sobsegway(speedMotor*-1, speedMotor,speedMotor*-1,speedMotor);
  Serial.print("ID: ");
  Serial.println(ID);
  Serial.print("Speed: ");
  Serial.println(speedMotor);
  Serial.println(" ");
  if (speedMotor>0){
    digitalWrite(LED2,HIGH);}
  else{
    digitalWrite(LED2,LOW);}
}

else if (inputString.substring(0,4) == "LEFT"){
  Serial.println("LEFT");
  String ID = inputString.substring(5,7);
  String speedM = inputString.substring(7,12);
  int speedMotor = speedM.toInt();
  motor.sobsegway(speedMotor*-1, speedMotor*-1,speedMotor*-1,speedMotor*-1);
  Serial.print("ID: ");
  Serial.println(ID);
  Serial.print("Speed: ");
  Serial.println(speedMotor);
  Serial.println(" ");
  if (speedMotor>0){
    digitalWrite(LED2,HIGH);}
  else{
    digitalWrite(LED2,LOW);}
}

else if (inputString.substring(0,5) == "RIGHT"){
  Serial.println("RIGHT");
  String ID = inputString.substring(6,8);
  String speedM = inputString.substring(8,13);
  int speedMotor = speedM.toInt();
  motor.sobsegway(speedMotor, speedMotor,speedMotor,speedMotor);
  Serial.print("ID: ");
  Serial.println(ID);
  Serial.print("Speed: ");
  Serial.println(speedMotor);
  Serial.println(" ");
  if (speedMotor>0){
    digitalWrite(LED2,HIGH);}
  else{
    digitalWrite(LED2,LOW);}
}

else{
  digitalWrite(LED2,LOW);
}

 // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void loop()
{
Command_serial();
//test_joystick();
}

