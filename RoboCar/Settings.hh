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
#define SPEED_MAX                       130

// Min speed of the motors (0 to 255)
// Values lower than 80 may not get the motor moving!
#define SPEED_MIN                       100

// How long to wait after power on, before taking over control
#define BOOT_UP_DELAY_S                 5

/*----------
   Sonar
----------*/

// Maximum distance we want to ping for (in centimeters)
// Maximum sensor distance is rated at 400-500cm.
#define SONAR_DISTANCE_MAX_CM           200

// How many pings, for a median reading (> 1)
// Lower count equals more probes per second.
// Higher count equals less false positives.
#define SONAR_PING_MEDIAN_COUNT         3

/*--------------------
   Obstacle evasion
--------------------*/

// Obstacle is close
#define OBSTACLE_PROXIMITY_CLOSE_CM     40

// Obstacle is EXTREMELY close
#define OBSTACLE_PROXIMITY_EXTREME_CM   15

// The obstacle evasion strategy (i.e. where to turn to)
// TODO: In the future, use 3 sonars to decide on which side
// to turn.
enum EVASION_STRATEGY { LEFT, RIGHT, RANDOM };
#define OBSTACLE_EVASION_STRATEGY       LEFT

// When we evade an extremely close obstacle, for how long to
// back-off at a time
#define OBSTACLE_EVASION_BACKING_MS     250

// When we evade a close obstacle, for how long do we turn
// at a time
#define OBSTACLE_EVASION_TURNING_MS     125