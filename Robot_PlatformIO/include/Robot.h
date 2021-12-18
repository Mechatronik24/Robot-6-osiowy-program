#include "RobotJoint.h"

class Robot
{
    int jointAngle[7];
    double smoothedAngle[7];
    double prevAngle[7];
    int reMap(int axisNumber);
    int iSpeed;
    double iX;
    double iY;
    double iZ;

public:
    Robot();                   // Constructor
    ~Robot();                  // Destructor
    void startupRobot();       // Attach servo 1 do 7 and write constructor's values
    RobotJoint iAxis[7];       // Create 7 iAxis objects
    void calculateXYZ();       // Calculate XYZ coordinates
    void update();             // Robot goes to new joint angles (joint move)
    int serialRead();          // Read digit data from terminal
    void setSpeed(int aSpeed); // Set robot speed from 1 to 100
};