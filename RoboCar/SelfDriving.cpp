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
#include "SelfDriving.hh"       // Responsible for the self-driving

/* -----------------------
    Private methods
----------------------- */

// Whether the next idle action should be a turn
bool _nextIdleActionShouldBeTurn = false;

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

    if (frontObstacleDistanceCm > 0 && frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_INRANGE_CM)
    {
        // Not turning and there's an obstacle within range ...
        // Now, from closest case to farthest ...

        if (frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_EXTREME_CM)
        {
            // Obstacle is extremely close

            // Hard stop
            stop(true);

            // Start backing-off slowly. Eventually it will get into the next range
            // of proximity (i.e. just 'close', instead of 'extreme') and will make
            // an evasive turn ...
            moveBackwards(SPEED_MIN, OBSTACLE_EVASION_BACKING_MS);

            // ... or will get out of obstacles range and the next action would be a turn
            _nextIdleActionShouldBeTurn = true;
        }
        else if (frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_CLOSE_CM)
        {
            // Obstacle is 'close', take an evasive turn based on strategy
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
                    _randomTurn(OBSTACLE_EVASION_RANDOM_TURN_MIN_MS, OBSTACLE_EVASION_RANDOM_TURN_MAX_MS);
                    break;
            }
        }
        else
        {
            // Obstacle is at least 'in range'
            // TODO: Slow down
        }
    }
    else if (isStopped())
    {
        // The bot is idle. Not turning, no obstacles, not moving
        // so take an 'idle action'.

        if (_nextIdleActionShouldBeTurn)
        {
            // Next idle action should be a turn, so turn
            _randomTurn(RANDOM_TURN_MIN_MS, RANDOM_TURN_MAX_MS);
        }
        else
        {
            // Next idle action shouldn't be a turn, so move forward at
            // for a while (5s to 10s)
            moveForward(SPEED_MAX, random(RANDOM_MOVEMENT_FWD_MIN_S, RANDOM_MOVEMENT_FWD_MAX_S)  * 1000);
        }

        // Make the next idle action the opposite (i.e. cycle them)
        _nextIdleActionShouldBeTurn = !_nextIdleActionShouldBeTurn;
    }
}