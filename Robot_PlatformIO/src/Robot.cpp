#include "Robot.h"
#include "Config.h"
Robot::Robot()
{
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
}

void Robot::calculateXYZ()
{
    // na podstawie tych iAxis1.iJoin... kalkulujemy x,y,z i podmieniamy tutaj

    iX = 0;
    iY = 0;
    iZ = 1;
}

void Robot::update()
{
    for (int i = 0; i < 7; i++)
    {
        iAxis[i].write(reMap(i));
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
        mappedAngle = map(iAxis[0].getJointAngle(), 0, 270, servo1Min, servo1Max);
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
        mappedAngle = map(iAxis[3].getJointAngle(), 0, 270, servo4Min, servo4Max);
        return mappedAngle;
        break;
    case 4:
        mappedAngle = map(iAxis[4].getJointAngle(), 0, 180, servo5Min, servo5Max);
        return mappedAngle;
        break;

    case 5:
        mappedAngle = map(iAxis[5].getJointAngle(), 0, 270, servo6Min, servo6Max);
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