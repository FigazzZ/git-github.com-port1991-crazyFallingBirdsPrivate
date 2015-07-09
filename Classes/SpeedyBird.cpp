//
//  SpeedyBird.cpp
//  FallingBirdsGame
//
//  Created by user on 30/06/15.
//
//

#include "SpeedyBird.h"

bool SpeedyBird::initBird(float xPos, BirdType bType)
{
    if ( !Bird::initBird(xPos, bType) ) {
        return false;
    }
    
    return true;
}

void SpeedyBird::updatePosition(float dt)
{
    Bird::updatePosition(dt);
}

void SpeedyBird::updateSpeed()
{
    speedFalling = singleton->getSpeedyBirdSpeed();
}