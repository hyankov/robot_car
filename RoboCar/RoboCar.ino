/*
    -----------------------------------------
    Self-driving, obstacle-avoiding robot car
    See: https://github.com/hyankov/robot_car
    -----------------------------------------
*/

// 1st party includes
#include "Pins.hh"              // Pin layout. Set pins according to your wiring
#include "Settings.hh"          // Include settings
#include "Movement.hh"          // Responsible for controlling the movements of the robot
#include "ObstacleDetection.hh" // Responsible for detecting obstacles
#include "SelfDriving.hh"       // Responsible for the self-driving

// Setup and initialize
void setup()
{
    // Random seed
    randomSeed(analogRead(PIN_UNUSED_ANALOG));

    // Setup the obstacle detection module
    setupObstacleDetection();

    // Setup the movements module
    setupMovement();

    // Setup the self-driving module
    setupSelfDriving();

    // Wait for a little while right after booting, to allow
    // people to back-off.
    delay(BOOT_UP_DELAY_S * 1000);
}

// The main loop, repeating over and over again
void loop()
{
    loopObstacleDetection();
    loopSelfDriving();
    loopMovement();
}