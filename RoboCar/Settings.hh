/*
    -----------------
    Various settings.
    -----------------
*/

#pragma once


/*----------
   Speed
----------*/

// Max speed of the motors (0 to 255)
#define SPEED_MAX                            120

// Min speed of the motors (0 to 255)
// Values lower than 80 may not get the motor moving!
#define SPEED_MIN                            90

// How long to wait after power on, before taking over control
#define BOOT_UP_DELAY_S                      3

/*----------
   Sonar
----------*/

// How many pings, for a median reading (> 1)
// Lower count equals more probes per second.
// Higher count equals less false positives.
#define SONAR_PING_MEDIAN_COUNT              3

/*--------------------
   Obstacle evasion
--------------------*/

// Note:
// OBSTACLE_PROXIMITY_INRANGE_CM > OBSTACLE_PROXIMITY_CLOSE_CM > OBSTACLE_PROXIMITY_EXTREME_CM

// Obstacle is in range (Don't exceed 400!)
#define OBSTACLE_PROXIMITY_INRANGE_CM        100

// Obstacle is close
#define OBSTACLE_PROXIMITY_CLOSE_CM          30

// Obstacle is EXTREMELY close
#define OBSTACLE_PROXIMITY_EXTREME_CM        15

// The obstacle evasion strategy (i.e. where to turn to)
// TODO: In the future, use 3 sonars to decide on which side
// to turn.
enum EVASION_STRATEGY { LEFT, RIGHT, RANDOM };
#define OBSTACLE_EVASION_STRATEGY            LEFT

// When we evade an extremely close obstacle, for how long to
// back-off at a time
#define OBSTACLE_EVASION_BACKING_MS          250

// When we evade a close obstacle, for how long do we turn
// at a time
#define OBSTACLE_EVASION_TURNING_MS          200

// For random turn evasion strategy, minimum turn time
#define OBSTACLE_EVASION_RANDOM_TURN_MIN_MS  500

// For random turn evasion strategy, maximum turn time
#define OBSTACLE_EVASION_RANDOM_TURN_MAX_MS  1000

/*----------------
   Self Driving
----------------*/

// When making a random idle turn, for how long to turn
// at minimum (ms)
#define RANDOM_TURN_MIN_MS                   200

// When making a random idle turn, for how long to turn
// at maximum (ms)
#define RANDOM_TURN_MAX_MS                   1200

// When making a random idle move forward, for how long to
// move at minimum (s)
#define RANDOM_MOVEMENT_FWD_MIN_S            5

// When making a random idle move forward, for how long to
// move at maximum (s)
#define RANDOM_MOVEMENT_FWD_MAX_S            10