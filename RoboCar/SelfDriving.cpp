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

// Randomly turns left or right, for a random time.
// - fromForHowLongMs: from duration in ms
// - toForHowLongMs: to duration in ms
void _randomTurn(long fromForHowLongMs, long toForHowLongMs)
{
    if (random(0, 2))
    {
        turnLeft(random(fromForHowLongMs, toForHowLongMs));
    }
    else
    {
        turnRight(random(fromForHowLongMs, toForHowLongMs));
    }
}

/* -----------------------
    Public methods
----------------------- */

void setupSelfDriving()
{
}

void loopSelfDriving()
{
    // Don't interrupt the turning of the robot.
    if (isTurning())
        return;

    // Ok, not turning, but might be moving ...

    if (frontObstacleDistanceCm > 0 && frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_CLOSE_CM)
    {
        // Not turning and there's an obstacle within range ...

        if (frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_EXTREME_CM)
        {
            // Obstacle is extremely close

            // Start backing-off slowly. Eventually it will get into the next range
            // of proximity and will make an evasive turn, or will get out of range
            // and will do a random turn or move forward again.
            moveBackwards(SPEED_MIN, OBSTACLE_EVASION_BACKING_MS);
        }
        else if (frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_CLOSE_CM)
        {
            // Obstacle is just close

            // based on evasion strategy
            switch (OBSTACLE_EVASION_STRATEGY)
            {
                case LEFT:
                    turnLeft(OBSTACLE_EVASION_TURNING_MS);
                    break;

                case RIGHT:
                    turnRight(OBSTACLE_EVASION_TURNING_MS);
                    break;

                case RANDOM:
                default:
                    // TODO: Pick a random direction to hold until the obstacle is evaded,
                    // and in this case use OBSTACLE_EVASION_TURNING_MS
                    _randomTurn(500, 1000);
                    break;
            }
        }
    }
    else if (isStopped())
    {
        // Not turning, no obstacles, not moving ...

        // 25% chance of ...
        if (random(0, 4) == 1)
        {
            _randomTurn(200, 2000);
        }
        else
        {
            // otherwise, start moving forward at a random speed, for a while (5s to 10s)
            moveForward(random(SPEED_MIN, SPEED_MAX), random(5, 10)  * 1000);
        }
    }
}