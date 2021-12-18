#include "Robot.h"
#include "Config.h"
#include <math.h>
Robot::Robot()
{
    prevAngle[0] = 90;
    prevAngle[1] = 90;
    prevAngle[2] = 90;
    prevAngle[3] = 90;
    prevAngle[4] = 90;
    prevAngle[5] = 90;
    prevAngle[6] = 90;
    iSpeed = 10;
}

Robot::~Robot()
{
}

void Robot::startupRobot()
{
    for (int i = 0; i <= 6; i++)
    {
        iAxis[i].attach(i + 4); // Attach serw od 1 do 7 na pinach od 4 do 10
    }
    update();
}

void Robot::calculateXYZ()
{
    // double iAlfa = iAxis[1].getJointAngle() * PI / 180;
    // double iBeta = (iAxis[2].getJointAngle() - 90 + iAxis[1].getJointAngle()) * PI / 180;
    // double iGamma = ((iAxis[4].getJointAngle() - 90) * PI / 180) + iBeta;

    // iX = shoulder1 * cos(iAlfa) + shoulder2 * cos(iBeta) + shoulder3 * cos(iGamma);
    // iY = shoulder1 * sin(iAlfa) + shoulder2 * sin(iBeta) + shoulder3 * sin(iGamma);

    double iAlfa = iAxis[0].getJointAngle() * PI / 180;                                    // Servo 1 degrees to radians
    double iBeta = iAxis[1].getJointAngle() * PI / 180;                                    // Servo 2 degrees to radians
    double iGamma = (iAxis[2].getJointAngle() - 90 + iAxis[1].getJointAngle()) * PI / 180; // Servo 3 degrees with offset to radians
    // double iDelta = iAxis[3].getJointAngle() * PI / 180;                                   // Servo 4 degrees to radians
    // double iEpsilon = ((iAxis[4].getJointAngle() - 90) * PI / 180) + iGamma;               // Servo 5 degrees with offset to radians

    iX = shoulder1 * cos(iAlfa) * cos(iBeta) + shoulder2 * cos(iAlfa) * cos(iGamma);
    iY = -(shoulder1 * sin(iAlfa) * cos(iBeta) + shoulder2 * sin(iAlfa) * cos(iGamma));
    iZ = shoulder1 * sin(iBeta) + shoulder2 * sin(iGamma);
    Serial.print("X: ");
    Serial.println(iX);
    Serial.print("Y: ");
    Serial.println(iY);
    Serial.print("Z: ");
    Serial.println(iZ);
}

void Robot::update()
{
    for (int i = 0; i < 7; i++)
    {
        jointAngle[i] = reMap(i);
    }
    while ((round(smoothedAngle[1]) != jointAngle[1]) || (round(smoothedAngle[2]) != jointAngle[2]) || (round(smoothedAngle[3]) != jointAngle[3]) || (round(smoothedAngle[4]) != jointAngle[4]) || (round(smoothedAngle[5]) != jointAngle[5]) || (round(smoothedAngle[6]) != jointAngle[6]))
    {
        for (int i = 0; i < 7; i++)
        {
            smoothedAngle[i] = ((jointAngle[i] * RobotAcceleration) + (prevAngle[i] * (1 - RobotAcceleration)));
            prevAngle[i] = smoothedAngle[i];
            iAxis[i].write(smoothedAngle[i]);
            delay(iSpeed);
        }
    }
}

int Robot::serialRead()
{
    while (Serial.available() == 0)
    {
    }
    int axisSelection = Serial.parseInt();
    int cleanup = Serial.parseInt();
    return axisSelection;
}

int Robot::reMap(int axisNumber)
{
    int mappedAngle = 0;
    switch (axisNumber)
    {
    case 0:
        mappedAngle = map(iAxis[0].getJointAngle(), -45, 225, servo1Min, servo1Max);
        return mappedAngle;
        break;
    case 1:
        mappedAngle = map(iAxis[1].getJointAngle(), 0, 180, servo2Min, servo2Max);
        return mappedAngle;
        break;
    case 2:
        mappedAngle = map(iAxis[2].getJointAngle(), 0, 180, servo3Min, servo3Max);
        return mappedAngle;
        break;
    case 3:
        mappedAngle = map(iAxis[3].getJointAngle(), -45, 225, servo4Min, servo4Max);
        return mappedAngle;
        break;
    case 4:
        mappedAngle = map(iAxis[4].getJointAngle(), 0, 180, servo5Min, servo5Max);
        return mappedAngle;
        break;

    case 5:
        mappedAngle = map(iAxis[5].getJointAngle(), -45, 225, servo6Min, servo6Max);
        return mappedAngle;
        break;
    case 6:
        mappedAngle = map(iAxis[6].getJointAngle(), 0, 180, servo7Min, servo7Max);
        return mappedAngle;
        break;
    default:
        return iAxis[axisNumber].getJointAngle();
        break;
    }
}

void Robot::setSpeed(int aSpeed) // ustawia prędkość robota wartość w zakresie od 1 do 100
{
    iSpeed = map(aSpeed, 1, 100, 100, 1);
}