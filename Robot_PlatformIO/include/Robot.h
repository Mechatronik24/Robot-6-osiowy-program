#include "RobotJoint.h"

class Robot
{
    int jointAngle[7];
    double smoothedAngle[7];
    double prevAngle[7];
    unsigned long iSpeed;
    int reMap(int axisNumber);
    int homeAngles[7] = {90, 170, 0, 90, 0, 90, 0}; // home servo angles
    int autoModeAngles[10][7] =
        {
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
            {90, 170, 0, 90, 0, 90, 0},
    };
    unsigned long t1[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned long t2[7];

public:
    Robot();             // Constructor
    ~Robot();            // Destructor
    void startupRobot(); // Attach servo 1 do 7 and write constructor's values
    RobotJoint iAxis[7]; // Create 7 iAxis objects
    void calculateXYZ(); // Calculate XYZ coordinates
    void updateAll();    // Robot goes to new joint angles (joint move)
    void update(int servoNumber);
    int serialRead();          // Read digit data from terminal
    void setSpeed(int aSpeed); // Set robot speed from 1 to 100
    int getSpeed();
    void home();
    void openGripper();
    void closeGripper();
    void setAutoModeAngles(int aX, int aY, int aValue);
    int getAutoModeAngles(int aX, int aY);
    double iX;
    double iY;
    double iZ;
};