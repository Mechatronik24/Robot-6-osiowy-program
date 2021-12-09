#include <arduino.h>
#include "Config.h"
#include "Robot.h"
#include "RobotJoint.h"

Robot robot;

int reading;

void setup()
{
  Serial.begin(9600);
  robot.startupRobot();
}

void loop()
{
  Serial.println("1. Zmiana kąta dowolnej osi");
  Serial.println("2. Update serw");
  reading = robot.serialRead();
  switch (reading)
  {
  case 1:
    Serial.print("Którą oś chcesz edytować? ");
    reading = robot.serialRead();
    Serial.print("Poprzednia wartość osi: ");
    Serial.println(robot.iAxis[reading - 1].getJointAngle());
    robot.iAxis[reading - 1].readJointAngleFromTerminal(reading);
    break;
  case 2:
    robot.update();
    break;
  default:
    Serial.println("Zły wybór!");
    break;
  }
}