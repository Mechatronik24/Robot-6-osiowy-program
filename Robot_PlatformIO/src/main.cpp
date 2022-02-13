#include <arduino.h>
#include "Config.h"
#include "Robot.h"
#include "RobotJoint.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(12, 11);
Robot robot;

int readMode;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  robot.startupRobot();
}

String BluetoothData, data1;
long data2;

void loop()
{
  while (bluetooth.available())
  {
    char z = bluetooth.read();
    BluetoothData += z;
    Serial.println(BluetoothData);
  }
  data1 = BluetoothData.substring(0, 6);
  BluetoothData.remove(0, 6);
  data2 = BluetoothData.toInt();
  BluetoothData.remove(0, BluetoothData.indexOf("S"));
  if (data1 == "ServoA")
  {
    robot.iAxis[0].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  else if (data1 == "ServoB")
  {
    robot.iAxis[1].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  else if (data1 == "ServoC")
  {
    robot.iAxis[2].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  else if (data1 == "ServoD")
  {
    robot.iAxis[3].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  else if (data1 == "ServoE")
  {
    robot.iAxis[4].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  else if (data1 == "ServoF")
  {
    robot.iAxis[5].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  else if (data1 == "ServoG")
  {
    robot.iAxis[6].setJointAngle(data2);
    // Serial.println(data1);
    // Serial.println(data2);
  }
  robot.update();
}

// void loop()
// {
//   Serial.println("1. New joint angle");
//   Serial.println("2. Update servos");
//   Serial.println("3. Change speed");
//   Serial.println("4. Calculate XYZ");
//   readMode = robot.serialRead();
//   switch (readMode)
//   {
//   case 1:
//     Serial.print("Which joint angle do you want to change? ");
//     readMode = robot.serialRead();
//     Serial.print("Previous joint angle: ");
//     Serial.println(robot.iAxis[readMode - 1].getJointAngle());
//     robot.iAxis[readMode - 1].readJointAngleFromTerminal(readMode);
//     break;
//   case 2:
//     robot.update();
//     break;
//   case 3:
//     robot.setSpeed(robot.serialRead());
//     break;
//   case 4:
//     robot.calculateXYZ();
//     break;
//   default:
//     Serial.println("Error!");
//     break;
//   }
// }