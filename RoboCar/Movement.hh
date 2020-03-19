/*
    --------------------------------------------------------
    The module which controls the movement of the robot car.
    -------------------------------------------------------
*/

#pragma once

// NOTE: To be invoked at initialization time!
void setupMovement();

// The main loop
void loopMovement();

// Whether the robot is currently turning.
// Note: it's also "Moving" if this is true.
bool isTurning();

// Whether the robot is currently stopped
bool isStopped();

// Move forward.
// - speed: [SPEED_MIN] to [SPEED_MAX]
// - forHowLongMs: for how long (in ms) to move forward
void moveForward(int speed, int forHowLongMs);

// Move backwards.
// - speed: [SPEED_MIN] to [SPEED_MAX]
// - forHowLongMs: for how long (in ms) to move forward
void moveBackwards(int speed, int forHowLongMs);

// Make a left turn.
// - forHowLongMs: for how long (in ms) to turn
void turnLeft(int forHowLongMs);

// Make a right turn.
// - forHowLongMs: for how long (in ms) to turn
void turnRight(int forHowLongMs);

// Stop.
// - isBrake: make a braking stop
void stop(bool isBrake);
