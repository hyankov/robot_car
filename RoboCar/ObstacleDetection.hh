/*
    ------------------------------------------------------------------
    The module which controls the obstacle detection of the robot car.
    ------------------------------------------------------------------
*/

// The distance to the obstacle in front
extern unsigned int frontObstacleDistanceCm;

//  NOTE: To be invoked at initialization time!
void setupObstacleDetection();

// The main loop
void loopObstacleDetection();