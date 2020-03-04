/*
    ------------------------------------------------------
    The module which controls the lights of the robot car.
    ------------------------------------------------------
*/

// 2nd party includes
#include "Arduino.h"

// 1st party includes
#include "Pins.hh"              // Pin layout. Set pins according to your wiring
#include "Settings.hh"          // Include settings
#include "Movement.hh"          // Responsible for controlling the movements of the robot
#include "ObstacleDetection.hh" // Responsible for detecting obstacles
#include "Lights.hh"            // Responsible for managing the lights of the car
#include "SelfDriving.hh"       // Responsible for the self-driving

/* -----------------------
    Private methods
----------------------- */

// Keep track whether the last movement was a turn
bool _lastActionWasTurn = false;

/* -----------------------
    Public methods
----------------------- */

void setupSelfDriving()
{
}

void loopSelfDriving()
{
    // If we are not moving (anymore)
    if (isStopped())
    {
        // if we didn't just finish making a turn ...
        if (!_lastActionWasTurn)
        {
            // making a random turn
            if (turn(random(-180, 180)))
            {
                _lastActionWasTurn = true;
            }
        }

        // if we didn't just start turning ...
        if (!isTurning())
        {
            // Start moving forward at a random speed, for a while (5s to 30s)
            moveForward(random(SPEED_MIN, SPEED_MAX), random(5 * 1000, 30 * 1000));

            // Reset flag
            _lastActionWasTurn = false;
        }
    }

    // If we're not currently turning and obstacle is within range ...
    if (!isTurning() && frontObstacleDistanceCm > 0 && frontObstacleDistanceCm <= OBSTACLE_LEVEL2_PROXIMITY_CM)
    {
        // Randomly turn 90 to 180 degrees, left or right. At the end
        // of the turn, the robot will stop moving.
        if (turn(random(90, 180) * (random(0, 2) == 0 ? 1 : -1)))
        {
            _lastActionWasTurn = true;
        }
    }
}