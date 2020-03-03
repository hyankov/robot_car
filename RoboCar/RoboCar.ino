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
#include "Pins.hh"          // Pin layout. Set pins according to your wiring
#include "Settings.hh"      // Include settings
#include "Movement.hh"      // Responsible for controlling the movements of the robot
#include "Sonar.hh"         // Responsible for detecting obstacles
#include "Lights.hh"        // Responsible for managing the lights of the car
#include "SelfDriving.hh"   // Responsible for the self-driving

// Setup and initialize
void setup()
{
    // Random seed
    randomSeed(analogRead(PIN_UNUSED_ANALOG));

    // Setup the movements module
    setupMovement();

    // Setup the sonar module
    setupSonar();

    // Setup the lights module
    setupLights();

    // Setup the self-driving module
    setupSelfDriving();

    // Wait for a little while right after booting, to allow
    // people to back-off.
    delay(BOOT_UP_DELAY_MS);
}

// The main loop, repeating over and over again
void loop()
{
    loopSonar();
    loopMovement();
    loopSelfDriving();
}