#include "RobotJoint.h"

class Robot
{
    int jointAngle[7];
    double smoothedAngle[7];
    double prevAngle[7];
    int reMap(int axisNumber);
    int iSpeed;

public:
    float iX;
    float iY;
    float iZ;
    Robot();
    ~Robot();
    void startupRobot();
    RobotJoint iAxis[7];
    void calculateXYZ();
    void update();
    // void update(int i, int jointAngle);
    int serialRead();
    void smoothMovement();
    void setSpeed(int aSpeed);
};