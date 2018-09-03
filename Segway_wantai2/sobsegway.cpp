
/*
 * Bismillahirohmanirrohim
  sobsegway.cpp - Library for acces BLDC Motor.
  Created by Muchammad Sobrun Ibnu Atfal, December 21, 2017.
  Released into the private domain.
  Research and Developtment.
  CT Asia Robotics Co.ltd.
  Copyright 2017
  all rights reserved
*/

#include "Arduino.h"
#include "sobsegway.h"


    int maxpwm = 255;
    int minpwm = -255;
    
    int kecepatan1 = 12;
    int dir1 = 11;
    int rem1 = 53;

    int kecepatan2 = 10;
    int dir2 = 9;
    int rem2 = 8;

    int kecepatan3 = 7;
    int dir3 = 5;
    int rem3 = 6;

    int kecepatan4 = 4;
    int dir4 = 2;
    int rem4 = 3;

    int EN1 = 48;
    int EN2 = 46;
    int EN3 = 44;
    int EN4 = 42;    

    //motor.init(13,36,34,10,11,7,6,38,40,12,8,9);
    
void motor::init(int kecepatana,int dira,int rema,int kecepatanb,int dirb,int remb,
                int kecepatany,int diry,int remy,int kecepatanz,int dirz,int remz)
{
  pinMode(kecepatana,OUTPUT);
  pinMode(dira,OUTPUT);
  pinMode(rema,OUTPUT);
  
  pinMode(kecepatanb,OUTPUT);
  pinMode(dirb,OUTPUT);
  pinMode(remb,OUTPUT);  

  pinMode(kecepatany,OUTPUT);
  pinMode(diry,OUTPUT);
  pinMode(remy,OUTPUT);
  
  pinMode(kecepatanz,OUTPUT);
  pinMode(dirz,OUTPUT);
  pinMode(remz,OUTPUT);

  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);
  pinMode(EN3,OUTPUT);
  pinMode(EN4,OUTPUT);  
}

void motor::sobsegway(int a, int b,int y,int z)
{
if (a > maxpwm){
   a = maxpwm;
  }
else if(a < minpwm){
   a = minpwm;
  }
  
if(b >maxpwm){
   b = maxpwm;
  }
else if(b < minpwm){
   b = minpwm;
  }
  
if (y > maxpwm){
   y = maxpwm;
  }
else if(y < minpwm){
   y = minpwm;
  }
  
if(z >maxpwm){
   z = maxpwm;
  }
else if(z < -maxpwm){
   z = -maxpwm;
  }

if( a < 0 )
  {
    int c = a*-1;
    analogWrite(kecepatan1,c);
    digitalWrite(dir1,LOW);     
  }
  else
  {
    analogWrite(kecepatan1,a);
    digitalWrite(dir1,HIGH);   
  }

if(b<0)
  { 
    int c1 = b*-1;
    analogWrite(kecepatan2,c1);
    digitalWrite(dir2,LOW);
  }
  else
  {
    analogWrite(kecepatan2,b);
    digitalWrite(dir2,HIGH); 
  }
  
if(y<0)
  { 
    int c = y*-1;
    analogWrite(kecepatan3,c);
    digitalWrite(dir3,LOW);
  }
  else
  {
    analogWrite(kecepatan3,y);
    digitalWrite(dir3,HIGH);    
  }

if(z<0)
  { 
    int c = z*-1;
    analogWrite(kecepatan4,c);
    digitalWrite(dir4,LOW);
  }
  else
  {
    analogWrite(kecepatan4,z);
    digitalWrite(dir4,HIGH);
  }
  digitalWrite(rem1,HIGH);
  digitalWrite(rem2,HIGH);
  digitalWrite(rem3,HIGH);
  digitalWrite(rem4,HIGH);
}

void motor::stoped()
{
    digitalWrite(rem1,LOW);
    digitalWrite(rem2,LOW);
    digitalWrite(rem3,LOW);
    digitalWrite(rem4,LOW);
}

void motor::enable()
{
    digitalWrite(EN1,LOW);
    digitalWrite(EN2,LOW);
    digitalWrite(EN3,LOW);
    digitalWrite(EN4,LOW);
}

void motor::disable()
{
    digitalWrite(EN1,HIGH);
    digitalWrite(EN2,HIGH);
    digitalWrite(EN3,HIGH);
    digitalWrite(EN4,HIGH);
}

