/*
    ------------------------------------------------------------------
    The module which controls the obstacle detection of the robot car.
    ------------------------------------------------------------------
*/

// 3rd party includes
#include <NewPing.h>

/* -----------------------
    Private methods
----------------------- */

// Updates the distance to the obstacle in front
void _updateObstacleProximity();

/* -----------------------
    Public methods
----------------------- */

// The distance to the obstacle in front
extern unsigned int frontObstacleDistanceCm;

//  NOTE: To be invoked at initialization time!
void setupObstacle();