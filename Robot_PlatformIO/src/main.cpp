#include <arduino.h>
#include "Config.h"
#include "Robot.h"
#include "RobotJoint.h"
#include <SoftwareSerial.h>
#include <MultiTasking.h>

SoftwareSerial bluetooth(12, 11);
Robot robot;

int readMode, data4[7], pointer = 0;
boolean updateState = 0, receivingState = 0;
unsigned long t3 = 0, t4;
String BluetoothData, data1, coordinatesTEXT, buffor;
long data2;
char data3;

void sendCoordinates();

void autoRobot();

void bluetoothRead();

void analizeBluetoothData();

//void terminal();

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  robot.startupRobot();
  superTask.addThread(bluetoothRead);
  superTask.addThread(analizeBluetoothData);
  //superTask.addThread(terminal);
  superTask.startTasks();
}

void loop()
{

}

// void terminal()
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

void sendCoordinates()
{
  buffor = robot.iX;
  coordinatesTEXT =buffor + "|";
  buffor = robot.iY;
  coordinatesTEXT = coordinatesTEXT + buffor + "|";
  buffor = robot.iZ;
  coordinatesTEXT = coordinatesTEXT + buffor + "|";
  bluetooth.print(coordinatesTEXT);
}

void autoRobot()
{
  for (int i = 0; i < 7; i++)
  {
    robot.iAxis[i].setJointAngle(robot.getAutoModeAngles(pointer, i));
  }
  Serial.print("Idę do pozycji: ");
  Serial.println(pointer + 1);
  robot.updateAll();
  sendCoordinates();
  pointer += 1;
  if (pointer >= 10)
  {
    pointer = 0;
  }
}

void bluetoothRead()
{
  while (bluetooth.available())
  {
    receivingState = 1;
    t4 = millis();
    if (t4 - t3 >= 5)
    {
      t3 = millis();
      char z = bluetooth.read();
      BluetoothData += z;
    }
  }
  receivingState = 0;
}

void analizeBluetoothData()
{
  if ((BluetoothData.length() > 1) && (receivingState == 0))
  {
    // Serial.println(BluetoothData);
    data1 = BluetoothData.substring(0, 5);
    BluetoothData.remove(0, 5);
    Serial.println(data1);
    if (data1 == "Servo")
    {
      updateState = 1;
      data3 = BluetoothData.charAt(0);
      BluetoothData.remove(0, 1);
      data2 = BluetoothData.toInt();
      BluetoothData.remove(0, BluetoothData.indexOf("S"));
      switch (data3)
      {
      case 'A':
        robot.iAxis[0].setJointAngle(data2);
        break;
      case 'B':
        robot.iAxis[1].setJointAngle(data2);
        break;
      case 'C':
        robot.iAxis[2].setJointAngle(data2);
        break;
      case 'D':
        robot.iAxis[3].setJointAngle(data2);
        break;
      case 'E':
        robot.iAxis[4].setJointAngle(data2);
        break;
      case 'F':
        robot.iAxis[5].setJointAngle(data2);
        break;
      case 'G':
        robot.iAxis[6].setJointAngle(data2);
        break;

      default:
        break;
      }
    }
    else if (data1 == "Speed")
    {
      data2 = BluetoothData.toInt();
      BluetoothData.remove(0, BluetoothData.indexOf("S"));
      robot.setSpeed(data2);
    }
    else if (data1 == "Sopen")
    {
      robot.openGripper();
    }
    else if (data1 == "Sclos")
    {
      robot.closeGripper();
    }
    else if (data1 == "Shome")
    {
      robot.home();
    }
    else if (data1 == "Sauto")
    {
      Serial.println("Jestem w Sauto a w stringu zostało: ");
      Serial.println(BluetoothData);
      data3 = BluetoothData.charAt(0);
      BluetoothData.remove(0, 1);
      // for (int i = 0; i < 7; i++)
      // {
      //   data4[i] = BluetoothData.toInt();
      //   BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
      // }
      switch (data3)
      {
      case 'A':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(0, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'B':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(1, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'C':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(2, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'D':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(3, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'E':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(4, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'F':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(5, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'G':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(6, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'H':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(7, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'I':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(8, i, BluetoothData.toInt());
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      case 'J':
        for (int i = 0; i < 7; i++)
        {
          robot.setAutoModeAngles(9, i, BluetoothData.toInt()); // robot.setAutoModeAngles(9, i, data4[i]);
          BluetoothData.remove(0, BluetoothData.indexOf("|") + 1);
        }
        break;
      default:
        break;
      }
    }
    else if (data1 == "Swork")
    {
      Serial.println("Jestem w work a w stringu zostało: ");
      Serial.println(BluetoothData);
      pointer = 0;
      superTask.setTimer(autoRobot, robot.getSpeed() * 100, 0);
    }
    else if (data1 == "Shalt")
    {
      Serial.println("Jestem w stop work a w stringu zostało: ");
      Serial.println(BluetoothData);
      superTask.killTimer(autoRobot);
    }
    else
    {
    }
  }
  else
  {
    if (updateState == 1)
    {
      robot.updateAll();
      Serial.println("Update");
      sendCoordinates();
      updateState = 0;
    }
  }
  data1 = "";
  data3 = '0';
}