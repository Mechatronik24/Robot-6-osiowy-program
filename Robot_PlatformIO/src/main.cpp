#include <arduino.h>
#include "Config.h"
#include "Robot.h"
#include "RobotJoint.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(12, 11);
Robot robot;

int readMode, updateState=0;
unsigned long t3=0, t4;
void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  robot.startupRobot();
}

String BluetoothData, data1,coordinatesTEXT,buffor;
long data2;

void loop()
{
  while (bluetooth.available())
  {
    t4= millis();
      if (t4 - t3 >= 5)
      {t3=millis();
    char z = bluetooth.read();
    BluetoothData += z;
      }

  }
  if (BluetoothData.length() > 1)
  { 
    updateState=1;
    Serial.println(BluetoothData);
    data1 = BluetoothData.substring(0, 6);
    BluetoothData.remove(0, 6);
    data2 = BluetoothData.toInt();
    BluetoothData.remove(0, BluetoothData.indexOf("S"));

    if (data1 == "ServoA")
    {
      robot.iAxis[0].setJointAngle(data2);
    }
    else if (data1 == "ServoB")
    {
      robot.iAxis[1].setJointAngle(data2);
    }
    else if (data1 == "ServoC")
    {
      robot.iAxis[2].setJointAngle(data2);
    }
    else if (data1 == "ServoD")
    {
      robot.iAxis[3].setJointAngle(data2);
    }
    else if (data1 == "ServoE")
    {
      robot.iAxis[4].setJointAngle(data2);
    }
    else if (data1 == "ServoF")
    {
      robot.iAxis[5].setJointAngle(data2);
    }
    else if (data1 == "ServoG")
    {
      robot.iAxis[6].setJointAngle(data2);
    }
  }
  else
  {
    if(updateState==1)
    {
    robot.updateAll();
    Serial.println("Update");
    buffor=robot.iX;
    coordinatesTEXT="|"+buffor+"|";
    buffor=robot.iY;
    coordinatesTEXT=coordinatesTEXT+buffor+"|";
    buffor=robot.iZ;
    coordinatesTEXT=coordinatesTEXT+buffor+"|";
    bluetooth.print(coordinatesTEXT);
    updateState=0;
    }
  }
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
//     robot.updateAll();
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