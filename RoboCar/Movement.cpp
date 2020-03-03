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

void _setMotorsDirection(bool leftIsBackwards, bool rightIsBackwards)
{
    // Left-side forwards or backwards
    digitalWrite(PIN_MOTORS_SIDE_LEFT_IN1, !leftIsBackwards ? HIGH : LOW);
    digitalWrite(PIN_MOTORS_SIDE_LEFT_IN2, leftIsBackwards ? HIGH : LOW);

    // Right-side forwards or backwards
    digitalWrite(PIN_MOTORS_SIDE_RIGHT_IN1, !rightIsBackwards ? HIGH : LOW);
    digitalWrite(PIN_MOTORS_SIDE_RIGHT_IN2, rightIsBackwards ? HIGH : LOW);
}

void _move(int speed, bool leftIsBackwards, bool rightIsBackwards)
{
    // Speed is MIN_SPEED to FULL_SPEED
    speed = constrain(speed, MIN_SPEED, FULL_SPEED);

    if (speed == FULL_SPEED)
    {
        // Both motor sides go at full speed ...
        digitalWrite(PIN_MOTORS_SIDE_LEFT_EN, HIGH);
        digitalWrite(PIN_MOTORS_SIDE_RIGHT_EN, HIGH);
    }
    else
    {
        // Both motor sides go at a specified speed ...
        analogWrite(PIN_MOTORS_SIDE_LEFT_EN, speed);
        analogWrite(PIN_MOTORS_SIDE_RIGHT_EN, speed);
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
    pinMode(PIN_MOTORS_SIDE_LEFT_EN, OUTPUT);
    pinMode(PIN_MOTORS_SIDE_LEFT_IN1, OUTPUT);
    pinMode(PIN_MOTORS_SIDE_LEFT_IN2, OUTPUT);

    // Right-side motor(s)
    pinMode(PIN_MOTORS_SIDE_RIGHT_EN, OUTPUT);
    pinMode(PIN_MOTORS_SIDE_RIGHT_IN1, OUTPUT);
    pinMode(PIN_MOTORS_SIDE_RIGHT_IN2, OUTPUT);
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
    // Stop the motors
    digitalWrite(PIN_MOTORS_SIDE_LEFT_EN, LOW);
    digitalWrite(PIN_MOTORS_SIDE_RIGHT_EN, LOW);

    // Is it a sudden brake?
    if (isBrake)
    {
        // Sudden stop left motors
        digitalWrite(PIN_MOTORS_SIDE_LEFT_IN1, LOW);
        digitalWrite(PIN_MOTORS_SIDE_LEFT_IN2, LOW);

        // Sudden stop right motors
        digitalWrite(PIN_MOTORS_SIDE_RIGHT_IN1, LOW);
        digitalWrite(PIN_MOTORS_SIDE_RIGHT_IN2, LOW);
    }
}

void turn(int degree)
{
    // No-op
    if (degree == 0) return;

    // Degree is -180 to 180
    degree = constrain(degree, -180, 180);

    // If we want to make a left turn, the left side moves
    // backwards and the right side moves forward.
    bool leftIsBackwards = degree < 0;
    _move(FULL_SPEED, leftIsBackwards, !leftIsBackwards);

    // Wait for the turn to complete, time it takes to make a 1 degree turn
    // at full speed, multiplied by the (abs) degrees we're turning.
    // TODO: Use adjustable resistor to increase/decrease how long a 180-deg
    // turn takes, because it might be different on different surfaces.
    delay((MOTOR_180_DEG_TURN_TIME_MS / 180.0) * abs(degree));

    // Stop
    stop(true);
}

void runMovementDiagnostics(long delayMs)
{
    // FWD - Accelerate from min to max
    for (int speed = MIN_SPEED; speed <= FULL_SPEED; speed++)
    {
        moveForward(speed);
        delay(delayMs);
    }

    // FWD - Decelerate from max to min
    for (int speed = FULL_SPEED; speed >= MIN_SPEED; speed--)
    {
        moveForward(speed);
        delay(delayMs);
    }

    // BWD - Accelerate from min to max
    for (int speed = MIN_SPEED; speed <= FULL_SPEED; speed++)
    {
        moveBackwards(speed);
        delay(delayMs);
    }

    // BWD - Decelerate from max to min
    for (int speed = FULL_SPEED; speed >= MIN_SPEED; speed--)
    {
        moveBackwards(speed);
        delay(delayMs);
    }

    // FWD - Full speed, sudden stop
    moveForward(FULL_SPEED);
    delay(delayMs * 100);
    stop(true);
    
    // BWD - Full speed, sudden stop
    moveBackwards(FULL_SPEED);
    delay(delayMs * 100);
    stop(true);

    // FWD - Move at minimum speed, soft stop
    moveForward(MIN_SPEED);
    delay(delayMs * 100);
    stop(false);

    // BWD - Move at minimum speed, soft stop
    moveBackwards(MIN_SPEED);
    delay(delayMs * 100);
    stop(false);

    // Turn left, 4 times
    turn(-45);
    delay(delayMs * 50);
    turn(-45);
    delay(delayMs * 50);
    turn(-45);
    delay(delayMs * 50);
    turn(-45);
    delay(delayMs * 50);

    // Turn right, 4 times
    turn(45);
    delay(delayMs * 50);
    turn(45);
    delay(delayMs * 50);
    turn(45);
    delay(delayMs * 50);
    turn(45);
    delay(delayMs * 50);
}