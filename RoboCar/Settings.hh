/*
    -----------------
    Various settings.
    -----------------
*/

#pragma once

// Max speed of the motors (0 to 255)
#define SPEED_MAX                       150

// Min speed of the motors (0 to 255)
// Values lower than 80 may not get the motor moving!
#define SPEED_MIN                       100

// How long to wait after power on, before taking over control
#define BOOT_UP_DELAY_MS                5000

// How long does it take (in ms) to make a 180 degree turn at
// max speed (1000 at 255)
#define MOTOR_180_DEG_TURN_TIME_MS      1600

// Maximum distance we want to ping for (in centimeters)
// Maximum sensor distance is rated at 400-500cm.
#define SONAR_DISTANCE_MAX_CM           200

// How many pings, for a median reading (> 1)
// Lower count equals more probes per second.
// Higher count equals less false positives.
#define SONAR_PING_MEDIAN_COUNT         3

// The obstacle evasion strategy (i.e. where to turn to)
// TODO: In the future, use 3 sonars to decide on which side
// to turn.
enum Evasion_Strategies { LEFT, RIGHT, RANDOM };
#define OBSTACLE_EVASION_STRATEGY       LEFT

// Obstacle is close
#define OBSTACLE_PROXIMITY_CLOSE_CM     50

// Obstacle is EXTREMELY close
#define OBSTACLE_PROXIMITY_EXTREME_CM   15