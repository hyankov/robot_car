/*
    -------------------------------------------------------
    Code for self-driving, obstacle-avoiding robot car.
                       Work in progress.
    -------------------------------------------------------
    
    Capabilities:
    - Move forward, backwards, make turns
    - Detect obstacles and make evasive maneuvers

    TODO:
    - Turn on headlights in low light conditions
    - Display information on a small display
*/

// 1st party includes
#include "Pins.hh"              // Pin layout. Set pins according to your wiring
#include "Settings.hh"          // Include settings
#include "Movement.hh"          // Responsible for controlling the movements of the robot
#include "ObstacleDetection.hh" // Responsible for detecting obstacles
#include "Lights.hh"            // Responsible for managing the lights of the car
#include "SelfDriving.hh"       // Responsible for the self-driving
#include "Display.hh"           // Responsible for the display

// Setup and initialize
void setup()
{
    // Random seed
    randomSeed(analogRead(PIN_UNUSED_ANALOG));

    // Setup the display module
    setupDisplay();

    // Setup the movements module
    setupMovement();

    // Setup the obstacle detection module
    setupObstacleDetection();

    // Setup the lights module
    setupLights();

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
    loopMovement();
    loopSelfDriving();
    loopDisplay();
}