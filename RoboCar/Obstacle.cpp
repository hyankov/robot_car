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
#include "Pins.hh"     // Pin layout. Set pins according to your wiring
#include "Settings.hh" // Include settings
#include "Obstacle.hh" // Method definitions

// 3rd party includes
#include <NewPing.h>

/* -----------------------
    Private methods
----------------------- */

unsigned long _previousMsPing = 0;
NewPing _sonar(PIN_ULTRASOUND_TRIG, PIN_ULTRASOUND_ECHO, SONAR_MAX_DISTANCE_CM);

/* -----------------------
    Public methods
----------------------- */

unsigned int frontObstacleDistanceCm = NO_ECHO;


void setupObstacle()
{
    // Bug: This doesn't work. See https://forum.arduino.cc/index.php?topic=420604.0
    // NewPing::timer_ms(SONAR_PING_FREQUENCY_MS, _updateObstacleProximity);
}

void loopObstacle()
{
    unsigned long currentMillis = millis();

    if (currentMillis - _previousMsPing >= SONAR_PING_FREQUENCY_MS)
    {
        // save the last time
        _previousMsPing = currentMillis;

        // Get the distance, in cm. Apply correction filter.
        frontObstacleDistanceCm = NewPing::convert_cm(_sonar.ping_median());
    }
}