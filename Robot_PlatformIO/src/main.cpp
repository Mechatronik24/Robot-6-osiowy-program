#include <arduino.h>
#include "Config.h"
#include "Robot.h"
#include "RobotJoint.h"

Robot robot;

int readMode;

void setup()
{
  Serial.begin(9600);
  robot.startupRobot();
}

void loop()
{
  Serial.println("1. New joint angle");
  Serial.println("2. Update servoes");
  Serial.println("3. Change speed");
  Serial.println("4. Calculate XYZ");
  readMode = robot.serialRead();
  switch (readMode)
  {
  case 1:
    Serial.print("Which joint do you want to change? ");
    readMode = robot.serialRead();
    Serial.print("Previous joint angle: ");
    Serial.println(robot.iAxis[readMode - 1].getJointAngle());
    robot.iAxis[readMode - 1].readJointAngleFromTerminal(readMode);
    break;
  case 2:
    robot.update();
    break;
  case 3:
    robot.setSpeed(robot.serialRead());
    break;
  case 4:
    robot.calculateXYZ();
    break;
  default:
    Serial.println("Error!");
    break;
  }
}