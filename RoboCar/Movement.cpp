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

// When (millis) to stop movement.
unsigned long _stopMovementAt = 0;

void _setMotorsDirection(bool leftIsBackwards, bool rightIsBackwards)
{
    // Left-side forwards or backwards
    digitalWrite(PIN_MOTORS_IN1_LEFT, !leftIsBackwards ? HIGH : LOW);
    digitalWrite(PIN_MOTORS_IN2_LEFT, leftIsBackwards ? HIGH : LOW);

    // Right-side forwards or backwards
    digitalWrite(PIN_MOTORS_IN1_RIGHT, !rightIsBackwards ? HIGH : LOW);
    digitalWrite(PIN_MOTORS_IN2_RIGHT, rightIsBackwards ? HIGH : LOW);
}

void _move(int speed, bool leftIsBackwards, bool rightIsBackwards, int forHowLongMs)
{
    // Constrain within legal limits
    speed = constrain(speed, 0, 255);

    // Both motor sides go at a specified speed ...
    analogWrite(PIN_MOTORS_EN_LEFT, speed);
    analogWrite(PIN_MOTORS_EN_RIGHT, speed);

    // Direct the motors the same way
    _setMotorsDirection(leftIsBackwards, rightIsBackwards);

    // Stop the movement at ...
    _stopMovementAt = millis() + forHowLongMs;
}

/* -----------------------
    Public methods
----------------------- */

void setupMovement()
{
    // Left-side motor(s)
    pinMode(PIN_MOTORS_EN_LEFT, OUTPUT);
    pinMode(PIN_MOTORS_IN1_LEFT, OUTPUT);
    pinMode(PIN_MOTORS_IN2_LEFT, OUTPUT);

    // Right-side motor(s)
    pinMode(PIN_MOTORS_EN_RIGHT, OUTPUT);
    pinMode(PIN_MOTORS_IN1_RIGHT, OUTPUT);
    pinMode(PIN_MOTORS_IN2_RIGHT, OUTPUT);
}

void loopMovement()
{
    unsigned long currentMillis = millis();

    // If it's time to stop the movement ...
    if (_stopMovementAt && currentMillis >= _stopMovementAt)
    {
        // Stop movement
        stop(true);
    }
}

bool isTurning()
{
    // See: 'Motor truth table' above. We're turning if ...
    return  
        // One of the motors is stopped, but the other is not
            (digitalRead(PIN_MOTORS_EN_LEFT) != digitalRead(PIN_MOTORS_EN_RIGHT))
        // or they're moving in different directions
        ||  (digitalRead(PIN_MOTORS_IN1_LEFT) != digitalRead(PIN_MOTORS_IN1_RIGHT))
        ||  (digitalRead(PIN_MOTORS_IN2_LEFT) != digitalRead(PIN_MOTORS_IN2_RIGHT));
}

bool isStopped()
{
   // See: 'Motor truth table' above. We're not moving if ...
   return
        // Left is stopped
        (
            // motor is stopped
                !digitalRead(PIN_MOTORS_EN_LEFT)
            // or IN1 & IN2 are equal (0 or 1)
            ||  (digitalRead(PIN_MOTORS_IN1_LEFT) == digitalRead(PIN_MOTORS_IN2_LEFT))
        )

        // and Right is stopped
        && (
            // motor is stopped
                !digitalRead(PIN_MOTORS_EN_RIGHT)
            // or IN1 & IN2 are equal (0 or 1)
            ||  (digitalRead(PIN_MOTORS_IN1_RIGHT) == digitalRead(PIN_MOTORS_IN2_RIGHT))
        );
}

void moveForward(int speed, int forHowLongMs)
{
    // Speed is constrained, SPEED_MIN to SPEED_MAX
    _move(constrain(speed, SPEED_MIN, SPEED_MAX), false, false, forHowLongMs);
}

void moveBackwards(int speed, int forHowLongMs)
{
    // Speed is constrained, SPEED_MIN to SPEED_MAX
    _move(constrain(speed, SPEED_MIN, SPEED_MAX), true, true, forHowLongMs);
}

void turnLeft(int forHowLongMs)
{
    // Speed is max possible
    _move(255, true, false, forHowLongMs);
}

void turnRight(int forHowLongMs)
{
    // Speed is max possible
    _move(255, false, true, forHowLongMs);
}

void stop(bool isBrake)
{
    // Is it a sudden brake?
    if (isBrake)
    {
        // Brake left motors
        digitalWrite(PIN_MOTORS_IN1_LEFT, LOW);
        digitalWrite(PIN_MOTORS_IN2_LEFT, LOW);

        // Brake right motors
        digitalWrite(PIN_MOTORS_IN1_RIGHT, LOW);
        digitalWrite(PIN_MOTORS_IN2_RIGHT, LOW);
    }
    else
    {
        // Gradual brake, just turn off power
        digitalWrite(PIN_MOTORS_EN_LEFT, LOW);
        digitalWrite(PIN_MOTORS_EN_RIGHT, LOW);
    }

    // Reset timer
    _stopMovementAt = 0;
}