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
#include "Pins.hh"      // Pin layout. Set pins according to your wiring
#include "Settings.hh"  // Include settings
#include "Sonar.hh"     // Method definitions

// 3rd party includes
#include <NewPing.h>

/* -----------------------
    Private methods
----------------------- */

unsigned long _previousMsPing = 0;
NewPing _sonar(PIN_SONAR_FRONT_TRIG, PIN_SONAR_FRONT_ECHO, SONAR_MAX_DISTANCE_CM);

/* -----------------------
    Public methods
----------------------- */

unsigned int frontObstacleDistanceCm = NO_ECHO;

void setupSonar()
{
    // Bug: This doesn't work. See https://forum.arduino.cc/index.php?topic=420604.0
    // NewPing::timer_ms(SONAR_PING_FREQUENCY_MS, _updateObstacleProximity);
}

void loopSonar()
{
    unsigned long currentMillis = millis();

    // Every SONAR_PING_FREQUENCY_MS milliseconds, update the distance to
    // the front obstacle
    if (currentMillis - _previousMsPing >= SONAR_PING_FREQUENCY_MS)
    {
        // save the last time
        _previousMsPing = currentMillis;

        // Get the distance, in cm. Apply correction filter.
        frontObstacleDistanceCm = NewPing::convert_cm(_sonar.ping_median());
    }
}