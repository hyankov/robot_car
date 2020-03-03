/*
    -----------------
    Various settings.
    -----------------
*/

#pragma once

// How long to wait after power on, before taking over control
#define BOOT_UP_DELAY_MS                2500

// How long does it take (in ms) to make a 180 degree turn
#define MOTOR_180_DEG_TURN_TIME_MS      1000

// Maximum distance we want to ping for (in centimeters)
// Maximum sensor distance is rated at 400-500cm.
#define SONAR_MAX_DISTANCE_CM           200

// How often to ping, in ms. Minimum should be 29
// When used in ping_median, it should be >= (5 * 30)
#define SONAR_PING_FREQUENCY_MS         200

// At how many cm proximity to avoid obstacles
#define AVOID_OBSTACLE_AT_PROXIMITY_CM  20