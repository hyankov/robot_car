/*
    --------------------------------------------------------
    The module which controls the movement of the robot car.
    -------------------------------------------------------
*/

#define FULL_SPEED 255
#define MIN_SPEED 65

/* -----------------------
    Private methods
----------------------- */

// Make the motors go forwards or backwards.
// - leftIsBackwards: whether the left-side motors go backwards
// - rightIsForwards: whether the right-side motors go backwards
void _setMotorsDirection(bool leftIsBackwards, bool rightIsBackwards);

// Move at a certain speed.
// - speed: [MIN_SPEED] to [FULL_SPEED]
// - leftIsBackwards: left moves backwards
// - rightIsBackwards: right moves backwards
void _move(int speed, bool leftIsBackwards, bool rightIsBackwards);

/* -----------------------
    Public methods
----------------------- */

//  NOTE: To be invoked at initialization time!
void setupMovement();

// Move forward.
// - speed: [MIN_SPEED] to [FULL_SPEED]
void moveForward(int speed);

// Move backwards.
// - speed: [MIN_SPEED] to [FULL_SPEED]
void moveBackwards(int speed);

// Stop.
// - isBrake: make a braking stop
void stop(bool isBrake);

// Make a turn.
// - degree: -180 to 180.
void turn(int degree);

// Run movement diagnostics.
// - delayMs: delay in ms between operations and in loops.
void runMovementDiagnostics(long delayMs);