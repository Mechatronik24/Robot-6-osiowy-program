#include "RobotJoint.h"

class Robot
{
    int reMap(int axisNumber);

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
    int serialRead();
};