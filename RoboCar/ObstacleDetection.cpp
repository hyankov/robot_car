/*
    ------------------------------------------------------------------
    The module which controls the obstacle detection of the robot car.
    ------------------------------------------------------------------

    See https://forum.arduino.cc/index.php?topic=106043.0
    See https://playground.arduino.cc/Code/NewPing
*/

// 2nd party includes
#include "Arduino.h"

// 1st party includes
#include "Pins.hh"                  // Pin layout. Set pins according to your wiring
#include "Settings.hh"              // Include settings
#include "ObstacleDetection.hh"     // Method definitions

// 3rd party includes
#include <NewPing.h>

/* -----------------------
    Private methods
----------------------- */

unsigned long _nextPingMs = 0;
NewPing _frontSonar(PIN_SONAR_TRIG_FRONT, PIN_SONAR_ECHO_FRONT, OBSTACLE_PROXIMITY_INRANGE_CM);

/* -----------------------
    Public methods
----------------------- */

unsigned int frontObstacleDistanceCm = NO_ECHO;

void setupObstacleDetection()
{
    // Bug: This doesn't work. See https://forum.arduino.cc/index.php?topic=420604.0
    // NewPing::timer_ms(SONAR_PING_FREQUENCY_MS, _updateObstacleProximity);
}

void loopObstacleDetection()
{
    unsigned long currentMs = millis();

    // Every (SONAR_PING_MEDIAN_COUNT * 30) milliseconds, update the distance to
    // the front obstacle
    if (currentMs >= _nextPingMs)
    {
        // Next ping time
        _nextPingMs = currentMs + (SONAR_PING_MEDIAN_COUNT * 30);

        // Get the distance, in cm. Apply correction filter.
        frontObstacleDistanceCm = NewPing::convert_cm(_frontSonar.ping_median(SONAR_PING_MEDIAN_COUNT));
    }
}