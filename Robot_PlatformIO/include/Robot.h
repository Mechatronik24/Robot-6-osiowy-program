#include "RobotJoint.h"

class Robot
{
    int jointAngle[7];
    double smoothedAngle[7];
    double prevAngle[7];
    unsigned long iSpeed;
    int reMap(int axisNumber);

public:
    Robot();                   // Constructor
    ~Robot();                  // Destructor
    void startupRobot();       // Attach servo 1 do 7 and write constructor's values
    RobotJoint iAxis[7];       // Create 7 iAxis objects
    void calculateXYZ();       // Calculate XYZ coordinates
    void updateAll();             // Robot goes to new joint angles (joint move)
    void update(int servoNumber);
    int serialRead();          // Read digit data from terminal
    void setSpeed(int aSpeed); // Set robot speed from 1 to 100
    double iX;
    double iY;
    double iZ;
};