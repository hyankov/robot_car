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
#include "Obstacle.hh"      // Responsible for detecting obstacles
#include "Lights.hh"        // Responsible for managing the lights of the car

// 3rd party includes
#include <timer.h>

// Setup and initialize
void setup()
{
    // Setup the movements module
    setupMovement();

    // Setup the obstacle module
    setupObstacle();

    // Setup the lights module
    setupLights();
}

unsigned long reset = millis();

// The main, repeatable loop
void loop()
{
    loopObstacle();
}