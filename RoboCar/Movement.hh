/*
    --------------------------------------------------------
    The module which controls the movement of the robot car.
    -------------------------------------------------------
*/

//  NOTE: To be invoked at initialization time!
void setupMovement();

// The main loop
void loopMovement();

// Whether the robot is currently turning.
// Note: it's also "Moving" if this is true.
bool isTurning();

// Whether the robot is currently stopped
bool isStopped();

// Move forward.
// - speed: [MIN_SPEED] to [MAX_SPEED]
// - forHowLongMs: for how long (in ms) to move forward
void moveForward(int speed, int forHowLongMs);

// Move backwards.
// - speed: [MIN_SPEED] to [MAX_SPEED]
// - forHowLongMs: for how long (in ms) to move forward
void moveBackwards(unsigned int speed, unsigned int forHowLongMs);

// Stop.
// - isBrake: make a braking stop
void stop(bool isBrake);

// Make a turn.
// - degree: -180 to 180. [0 to -180] is Left turn,
// [0 to 180] is Right turn.
bool turn(int degree);
