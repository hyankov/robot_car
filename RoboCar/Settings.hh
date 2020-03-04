/*
    -----------------
    Various settings.
    -----------------
*/

#pragma once

// Max speed of the motors
#define SPEED_MAX                       200

// Min speed of the motors
#define SPEED_MIN                       100

// How long to wait after power on, before taking over control
#define BOOT_UP_DELAY_MS                5000

// How long does it take (in ms) to make a 180 degree turn
#define MOTOR_180_DEG_TURN_TIME_MS      1000

// Maximum distance we want to ping for (in centimeters)
// Maximum sensor distance is rated at 400-500cm.
#define SONAR_DISTANCE_MAX_CM           200

// How often to ping, in ms. Minimum should be 29
// When used in ping_median, it should be >= (NumberOfPings * 30)
#define SONAR_PING_FREQUENCY_MS         150

// Obstacle is close
#define OBSTACLE_PROXIMITY_CLOSE_CM     40

// Obstacle is EXTREMELY close
#define OBSTACLE_PROXIMITY_EXTREME_CM   10