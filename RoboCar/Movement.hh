/*
    --------------------------------------------------------
    The module which controls the movement of the robot car.
    -------------------------------------------------------
*/

#define MAX_SPEED 255
#define MIN_SPEED 65

//  NOTE: To be invoked at initialization time!
void setupMovement();

// The main loop
void loopMovement();

// Whether the robot is currently moving
bool isMoving();

// Move forward.
// - speed: [MIN_SPEED] to [MAX_SPEED]
void moveForward(int speed);

// Move backwards.
// - speed: [MIN_SPEED] to [MAX_SPEED]
void moveBackwards(int speed);

// Stop.
// - isBrake: make a braking stop
void stop(bool isBrake);

// Make a turn.
// - degree: -180 to 180.
void turn(int degree);
