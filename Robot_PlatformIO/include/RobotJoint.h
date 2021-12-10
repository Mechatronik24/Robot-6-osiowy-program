#pragma once
#include <arduino.h>
#include <Servo.h>

class RobotJoint : public Servo
{
  int iJointAngle;

public:
  RobotJoint();
  ~RobotJoint();
  void setJointAngle(int aJointAngle);
  int getJointAngle();
  void readJointAngleFromTerminal(int a);
};