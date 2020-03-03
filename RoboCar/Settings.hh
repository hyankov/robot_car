/*
    -----------------
    Various settings.
    -----------------
*/

#pragma once

// How long does it take (in ms) to make a 180 degree turn
#define MOTOR_180_DEG_TURN_TIME_MS 800

// Maximum distance we want to ping for (in centimeters).
// Maximum sensor distance is rated at 400-500cm.
#define SONAR_MAX_DISTANCE_CM 200

// How often to ping, in ms. Minimum should be 29.
// When used in ping_median, it should be >= (5 * 30)
#define SONAR_PING_FREQUENCY_MS 200

// At how many cm proximity to avoid obstacles
#define AVOID_OBSTACLES_AT_CM 20