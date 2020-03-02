/*
    -------------------------------------------------------
    Code for obstacle-avoiding robot car. Work in progress.
    -------------------------------------------------------
    
    Capabilities:
    - Move forward, backwards, make turns
    - Detect obstacles and make evasive maneuvers
    - Turn on headlights in low light conditions (TODO)
    - Display information on a small display (TODO)
    
    Modes:
    - Autonomous - roam around and avoid obstacles
    - Manual - receive input from a remote control (bluetooth or IR)
*/

// Misc
#include "Pins.hh"              // Pin layout. Set pins according to your wiring
#include "Settings.hh"          // Include settings

// Modules
#include "Movement.hh"         // Responsible for controlling the movements of the robot
#include "Obstacle.hh"         // Responsible for detecting obstacles
#include "Lights.hh"           // Responsible for managing the lights of the car
#include "ManualControl.hh"    // Responsible for receiving manual control commands

// Setup and initialize
void setup()
{
    // Setup the movements module
    setupMovement();

    // Setup the obstacle module
    setupObstacle();

    // Setup the lights module
    setupLights();

    // Setup the manual control module
    setupManualControl();
}

void loop()
{
    // TODO:
}