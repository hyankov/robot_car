/*
    ------------------------------------------------------
    The module which controls the lights of the robot car.
    ------------------------------------------------------
*/

// 2nd party includes
#include "Arduino.h"

// 1st party includes
#include "Pins.hh"          // Pin layout. Set pins according to your wiring
#include "Settings.hh"      // Include settings
#include "Movement.hh"      // Responsible for controlling the movements of the robot
#include "Sonar.hh"         // Responsible for detecting obstacles
#include "Lights.hh"        // Responsible for managing the lights of the car
#include "SelfDriving.hh"   // Responsible for the self-driving

/* -----------------------
    Public methods
----------------------- */

void setupSelfDriving()
{
}

void loopSelfDriving()
{
    // If we are not moving
    if (!isMoving())
    {
        // Start moving forward at a random speed
        moveForward(random(MIN_SPEED, MAX_SPEED));
    }

    // If obstacle is within range ...
    if (frontObstacleDistanceCm > 0 && frontObstacleDistanceCm <= AVOID_OBSTACLE_AT_PROXIMITY_CM)
    {
        // Randomly turn 90 to 180 or -90 to -180 degrees. At the end
        // of the turn, the robot will stop moving. Multiple overlapping
        // turns will be ignored. i.e. no new turn will begin until the
        // old one finishes.
        turn(random(90, 180) * (random(0, 2) == 0 ? 1 : -1));
    }
}