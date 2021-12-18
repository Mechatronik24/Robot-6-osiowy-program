#pragma once
#include <arduino.h>
#include <Servo.h>

class RobotJoint : public Servo
{
  int iJointAngle;

public:
  RobotJoint();                           // Constructor
  ~RobotJoint();                          // Destructor
  void setJointAngle(int aJointAngle);    // Set new joint angle
  int getJointAngle();                    // Get joint angle from class RobotJoint
  void readJointAngleFromTerminal(int a); // Read joint angle
};