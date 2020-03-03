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
#include "Obstacle.hh"  // Method definitions

// 3rd party includes
#include <NewPing.h>

/* -----------------------
    Private methods
----------------------- */

NewPing _sonar(PIN_ULTRASOUND_TRIG, PIN_ULTRASOUND_ECHO, SONAR_MAX_DISTANCE_CM);

void _updateObstacleProximity()
{
    // Get the distance, in cm.
    frontObstacleDistanceCm = _sonar.ping_cm();
}

/* -----------------------
    Public methods
----------------------- */

unsigned int frontObstacleDistanceCm = NO_ECHO;

void setupObstacle()
{
    pinMode(PIN_ULTRASOUND_TRIG, OUTPUT);
    pinMode(PIN_ULTRASOUND_ECHO, INPUT);

    NewPing::timer_ms(SONAR_PING_FREQUENCY_MS, _updateObstacleProximity);
}