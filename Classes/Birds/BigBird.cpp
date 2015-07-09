//
//  BigBird.cpp
//  FallingBirdsGame
//
//  Created by user on 01/07/15.
//
//

#include "BigBird.h"


bool BigBird::initBird(float xPos, BirdType bType)
{
    if( !Bird::initBird(xPos, bType))
    {
        return false;
    }
    
    speedFalling = singleton->getBigBirdSpeed();
    
    return true;
}

void BigBird::initSprite(float xPos)
{
    char *frameName = new char;
    sprintf(frameName, "bird_%d_0.png", birdType);
    
    sprObject = Sprite::createWithSpriteFrameName(frameName);
    if(xPos < winSize.width*0.5f)
    {
        sprObject->setPosition(-winSize.width*0.15, winSize.height*0.8f);   //0.8f is optional. It will be more randomly later
        vectorFalling = Vec2(0.7f, 0.3f);
    }
    else
    {
        sprObject->setPosition(winSize.width*1.15, winSize.height*0.8f);
        sprObject->setFlippedX(true);
        vectorFalling = Vec2(-0.7f, 0.3f);
    }
    this->addChild(sprObject);
    
    delete []frameName;
}

void BigBird::updatePosition(float dt)
{
    if(singleton->isPaused() || singleton->isGameOver())
        return;
    
    this->changeVectorFalling(dt);
    
    Bird::updatePosition(dt);
}

void BigBird::changeVectorFalling(float dt)
{
    vectorFalling.y = vectorFalling.y - fallingCoefficient * dt;
    vectorFalling.normalize();
}

void BigBird::updateSpeed()
{
    speedFalling = singleton->getBigBirdSpeed();
    
    if(singleton->getBigBirdSpeed() == SLOWING_BIRD_SPEED)
    {
        fallingCoefficient = fallingCoefficient/10.0f;
    }
    else
    {
        fallingCoefficient = FALLING_COEFFICIENT;
    }
}