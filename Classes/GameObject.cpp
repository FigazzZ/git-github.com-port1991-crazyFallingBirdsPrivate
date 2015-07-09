//
//  GameObject.cpp
//  FallingBirdsGame
//
//  Created by user on 24/06/15.
//
//

#include "GameObject.h"
#include "Constants.h"

bool GameObject::init()
{
    if ( !Layer::init()) {
        return false;
    }
    
    return true;
}

void GameObject::launchFalling()
{
    this->schedule(schedule_selector(GameObject::updatePosition));
}

void GameObject::updatePosition(float dt)
{
    if(singleton->isPaused())
        return;
    
    if (singleton->isGameOver()) {
        return;
    }
    
    float speedX = vectorFalling.x * speedFalling;
    float speedY = vectorFalling.y * speedFalling;
    sprObject->setPosition(sprObject->getPositionX() + speedX, sprObject->getPositionY() + speedY);
}

void GameObject::deleteObject()
{
    this->removeFromParentAndCleanup(true);
}