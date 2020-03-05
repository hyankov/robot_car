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
    Public methods
----------------------- */

void setupSelfDriving()
{
}

void loopSelfDriving()
{
    // Don't interrupt the turning of the robot.
    if (isTurning()) return;

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
            moveBackwards(SPEED_MIN, 200);
        }
        else if (frontObstacleDistanceCm <= OBSTACLE_PROXIMITY_CLOSE_CM)
        {
            // Obstacle is just close

            // based on evasion strategy
            switch (OBSTACLE_EVASION_STRATEGY)
            {
                case LEFT:
                    // Random left turn (> 90deg)
                    turn(random(-90, -180));
                    break;
                
                case RIGHT:
                    // Random right turn (> 90deg)
                    turn(random(90, 180));
                    break;

                case RANDOM:
                default:
                    // Random left or right (> 90deg)
                    turn(random(90, 180) * (random(0, 2) == 0 ? 1 : -1));
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
            // making a random turn
            turn(random(-180, 180));
        }
        else
        {
            // otherwise, start moving forward at a random speed, for a while (5s to 10s)
            moveForward(random(SPEED_MIN, SPEED_MAX), random(5 * 1000, 10 * 1000));
        }
    }
}