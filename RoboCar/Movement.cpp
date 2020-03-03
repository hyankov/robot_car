/*
    --------------------------------------------------------
    The module which controls the movement of the robot car.
    -------------------------------------------------------

    See https://www.14core.com/wiring-driving-the-l298n-h-bridge-on-2-to-4-dc-motors
    See https://dronebotworkshop.com/dc-motors-l298n-h-bridge

    -------------------------------------------------
    |              Motor truth table                |
    -------------------------------------------------
    ENA	IN1	IN2	Description
    -----------------------
    0	N/A	N/A	Motor is off
    1	0	0	Motor is stopped (brakes)
    1	0	1	Motor is on and turning backwards
    1	1	0	Motor is on and turning forwards
    -------------------------------------------------
    1	1	1	Motor is stopped (brakes) - Don't use
    --------------------------------------------------
*/

// 2nd party includes
#include "Arduino.h"

// 1st party includes
#include "Pins.hh"      // Pin layout. Set pins according to your wiring
#include "Settings.hh"  // Include settings
#include "Movement.hh"  // Method definitions

/* -----------------------
    Private methods
----------------------- */

// When (millis) to stop turning (if making a turn).
unsigned long _stopTurningAt = 0;

void _setMotorsDirection(bool leftIsBackwards, bool rightIsBackwards)
{
    // Left-side forwards or backwards
    digitalWrite(PIN_MOTORS_LEFT_IN1, !leftIsBackwards ? HIGH : LOW);
    digitalWrite(PIN_MOTORS_LEFT_IN2, leftIsBackwards ? HIGH : LOW);

    // Right-side forwards or backwards
    digitalWrite(PIN_MOTORS_RIGHT_IN1, !rightIsBackwards ? HIGH : LOW);
    digitalWrite(PIN_MOTORS_RIGHT_IN2, rightIsBackwards ? HIGH : LOW);
}

void _move(int speed, bool leftIsBackwards, bool rightIsBackwards)
{
    // Speed is MIN_SPEED to MAX_SPEED
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);

    if (speed == MAX_SPEED)
    {
        // Both motor sides go at full speed ...
        digitalWrite(PIN_MOTORS_LEFT_EN, HIGH);
        digitalWrite(PIN_MOTORS_RIGHT_EN, HIGH);
    }
    else
    {
        // Both motor sides go at a specified speed ...
        analogWrite(PIN_MOTORS_LEFT_EN, speed);
        analogWrite(PIN_MOTORS_RIGHT_EN, speed);
    }

    // Direct the motors the same way
    _setMotorsDirection(leftIsBackwards, rightIsBackwards);
}

/* -----------------------
    Public methods
----------------------- */

void setupMovement()
{
    // Left-side motor(s)
    pinMode(PIN_MOTORS_LEFT_EN, OUTPUT);
    pinMode(PIN_MOTORS_LEFT_IN1, OUTPUT);
    pinMode(PIN_MOTORS_LEFT_IN2, OUTPUT);

    // Right-side motor(s)
    pinMode(PIN_MOTORS_RIGHT_EN, OUTPUT);
    pinMode(PIN_MOTORS_RIGHT_IN1, OUTPUT);
    pinMode(PIN_MOTORS_RIGHT_IN2, OUTPUT);
}

void loopMovement()
{
    unsigned long currentMillis = millis();

    // If it's time to stop the turn movement ...
    if (_stopTurningAt && currentMillis >= _stopTurningAt)
    {
        // Stop movement
        stop(true);

        // Reset timer
        _stopTurningAt = 0;
    }
}

bool isMoving()
{
   // See: 'Motor truth table' above. We're not moving if ...
   return 
        // Left is stopped
        (
            // motor is stopped
                !digitalRead(PIN_MOTORS_LEFT_EN)
            // or IN1 & IN2 are equal (0 or 1)
            || (digitalRead(PIN_MOTORS_LEFT_IN1) == digitalRead(PIN_MOTORS_LEFT_IN2))
        )

        // and Right is stopped
        && (
            // motor is stopped
                !digitalRead(PIN_MOTORS_RIGHT_EN)
            // or IN1 & IN2 are equal (0 or 1)
            || (digitalRead(PIN_MOTORS_RIGHT_IN1) == digitalRead(PIN_MOTORS_RIGHT_IN2))
        );
}

void moveForward(int speed)
{
    _move(speed, false, false);
}

void moveBackwards(int speed)
{
    _move(speed, true, true);
}

void stop(bool isBrake)
{
    // Is it a sudden brake?
    if (isBrake)
    {
        // Brake left motors
        digitalWrite(PIN_MOTORS_LEFT_IN1, LOW);
        digitalWrite(PIN_MOTORS_LEFT_IN2, LOW);

        // Brake right motors
        digitalWrite(PIN_MOTORS_RIGHT_IN1, LOW);
        digitalWrite(PIN_MOTORS_RIGHT_IN2, LOW);
    }
    else
    {
        // Gradual brake, just turn off power
        digitalWrite(PIN_MOTORS_LEFT_EN, LOW);
        digitalWrite(PIN_MOTORS_RIGHT_EN, LOW);
    }
}

void turn(int degree)
{
    // If degree is 0 or we're already making a turn ...
    if (degree == 0 || _stopTurningAt > 0) return;

    // Degree is -180 to 180
    degree = constrain(degree, -180, 180);

    // If we want to make a left turn, the left side moves
    // backwards and the right side moves forward.
    bool leftIsBackwards = degree < 0;
    _move(MAX_SPEED, leftIsBackwards, !leftIsBackwards);

    // Stop movement after the time it takes to make a 1 degree turn at full
    // speed, multiplied by the (abs) degrees we're turning.
    // TODO: Use adjustable resistor to increase/decrease how long a 180-deg
    // turn takes, because it might be different on different surfaces.
    int expectedTurnTimeMs = (MOTOR_180_DEG_TURN_TIME_MS / 180.0) * abs(degree);

    // Stop the movement at ...
    _stopTurningAt = millis() + expectedTurnTimeMs;
}