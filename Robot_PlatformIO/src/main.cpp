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
  Serial.println("1. Zmiana kąta dowolnej osi");
  Serial.println("2. Update serw");
  Serial.println("3. Zmiana prędkości");
  readMode = robot.serialRead();
  switch (readMode)
  {
  case 1:
    Serial.print("Którą oś chcesz edytować? ");
    readMode = robot.serialRead();
    Serial.print("Poprzednia wartość osi: ");
    Serial.println(robot.iAxis[readMode - 1].getJointAngle());
    robot.iAxis[readMode - 1].readJointAngleFromTerminal(readMode);
    break;
  case 2:
    robot.update();
    break;
  case 3:
    robot.setSpeed(robot.serialRead());
    break;
  default:
    Serial.println("Zły wybór!");
    break;
  }
}