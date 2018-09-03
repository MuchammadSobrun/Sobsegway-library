/*
 * Bismillahirohmanirrohim
  sobsegway.h - Library for acces BLDC Motor.
  Created by Muchammad Sobrun Ibnu Atfal, December 21, 2017.
  Released into the private domain.
  Research and Developtment.
  CT Asia Robotics Co.ltd.
  Copyright 2017
  all rights reserved  
*/

#ifndef sobsegway_h
#define sobsegway_h

#include "Arduino.h"

class motor
{
  public:
    void sobsegway(int a, int b,int y,int z);
    void init (int kecepatana  ,int dira ,int rema ,int kecepatanb  ,int dirb ,int remb ,
                int kecepatanay  ,int diry ,int remy ,int kecepatanz,int dirz ,int remz );
                
    void motor::stoped();
    void motor::enable();
    void motor::disable();

  private:
    
};

#endif
