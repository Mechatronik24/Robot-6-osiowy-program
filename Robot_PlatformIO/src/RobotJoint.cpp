
#include "RobotJoint.h"

#include "Config.h"

RobotJoint::RobotJoint()
{
    iJointAngle = 90;
}

RobotJoint::~RobotJoint()
{
}

void RobotJoint::setJointAngle(int aJointAngle)
{
    iJointAngle = aJointAngle;
}

int RobotJoint::getJointAngle()
{
    return iJointAngle;
}

void RobotJoint::readJointAngleFromTerminal(int a)
{
    Serial.print("Podaj wartość nowego kąta osi ");
    Serial.print(a);
    Serial.print(": ");
    while (Serial.available() == 0)
    {
    }
    iJointAngle = Serial.parseInt();
    int cleanup = Serial.parseInt();
    Serial.println(iJointAngle);

    // jointAngle[a-1]=Serial.parseInt();
    // Serial.println( jointAngle[a-1]);
}