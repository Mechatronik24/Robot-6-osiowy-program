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
    iSpeed = 30;
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
    updateAll();
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
    // double iDelta = (2 * (iAxis[1].getJointAngle() - 90) + iAxis[1].getJointAngle() - 90) * PI / 180; // X axis rotation of shoulder1 and 2
    // double iEpsilon = ((iAxis[3].getJointAngle() - 90) * PI / 180)+iAlfa; // Z axis rotation of shoulder1 and 2
    double iZeta = ((iAxis[4].getJointAngle() - 90) * PI / 180) + iGamma; // Servo 5 degrees to radians

    iX = -(shoulder1 * cos(iAlfa) * cos(iBeta) + shoulder2 * cos(iAlfa) * cos(iGamma) + shoulder3 * cos(iAlfa) * cos(iZeta)); // XYZ without servo 4 rotation
    iY = -(shoulder1 * sin(iAlfa) * cos(iBeta) + shoulder2 * sin(iAlfa) * cos(iGamma) + shoulder3 * sin(iAlfa) * cos(iZeta));
    iZ = shoulder1 * sin(iBeta) + shoulder2 * sin(iGamma) + shoulder3 * sin(iZeta);
    Serial.print("X: ");
    Serial.println(iX);
    Serial.print("Y: ");
    Serial.println(iY);
    Serial.print("Z: ");
    Serial.println(iZ);
}
void Robot::updateAll()
{
    for (int i = 0; i < 7; i++)
    {
        jointAngle[i] = reMap(i);
    }
    while ((round(smoothedAngle[1]) != jointAngle[1]) || (round(smoothedAngle[2]) != jointAngle[2]) || (round(smoothedAngle[3]) != jointAngle[3]) || (round(smoothedAngle[4]) != jointAngle[4]) || (round(smoothedAngle[5]) != jointAngle[5]) || (round(smoothedAngle[6]) != jointAngle[6]))
    {
        for (int i = 0; i < 7; i++)
        {
            t2[i] = millis();
            if ((t2[i] - t1[i] >= iSpeed) && (abs(jointAngle[i] - prevAngle[i]) > 3))
            {
                t1[i] = millis();
                smoothedAngle[i] = ((jointAngle[i] * RobotAcceleration) + (prevAngle[i] * (1 - RobotAcceleration))); // 1 - RobotAcceleration
                prevAngle[i] = smoothedAngle[i];
                iAxis[i].write(smoothedAngle[i]);
            }
            else if (abs(jointAngle[i] - prevAngle[i]) <= 3)
            {
                smoothedAngle[i] = jointAngle[i];
                iAxis[i].write(smoothedAngle[i]);
            }
        }
    }
    calculateXYZ();
}
void Robot::update(int servoNumber)
{
    jointAngle[servoNumber] = reMap(servoNumber);
    while (round(smoothedAngle[servoNumber]) != jointAngle[servoNumber])
    {
        if (abs(jointAngle[servoNumber] - prevAngle[servoNumber]) > 3)
        {
            smoothedAngle[servoNumber] = ((jointAngle[servoNumber] * RobotAcceleration) + (prevAngle[servoNumber] * (1 - RobotAcceleration))); // 1 - RobotAcceleration
            prevAngle[servoNumber] = smoothedAngle[servoNumber];
            delay(iSpeed);
        }
        else
        {
            smoothedAngle[servoNumber] = jointAngle[servoNumber];
        }
        // Serial.println(smoothedAngle[servoNumber]);
        iAxis[servoNumber].write(smoothedAngle[servoNumber]);
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
        mappedAngle = map(iAxis[6].getJointAngle(), 0, 90, servo7Min, servo7Max);
        return mappedAngle;
        break;
    default:
        return iAxis[axisNumber].getJointAngle();
        break;
    }
}

void Robot::setSpeed(int aSpeed) // ustawia prędkość robota wartość w zakresie od 1 do 100
{
    iSpeed = map(aSpeed, 10, 100, 100, 10);
}

int Robot::getSpeed()
{
    return iSpeed;
}

void Robot::home()
{
    for (int i = 0; i < 7; i++)
    {
        iAxis[i].setJointAngle(homeAngles[i]);
    }
    updateAll();
}

void Robot::openGripper()
{
    iAxis[6].setJointAngle(0);
    update(6);
}

void Robot::closeGripper()
{
    iAxis[6].setJointAngle(90);
    update(6);
}

void Robot::setAutoModeAngles(int aX, int aY, int aValue)
{
    autoModeAngles[aX][aY] = aValue;
}

int Robot::getAutoModeAngles(int aX, int aY)
{
    return autoModeAngles[aX][aY];
}