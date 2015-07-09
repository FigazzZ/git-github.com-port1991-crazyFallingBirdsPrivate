//
//  Booster.cpp
//  FallingBirdsGame
//
//  Created by user on 24/06/15.
//
//

#include "Booster.h"

Booster* Booster::createBooster(BoosterType bType, float xPos)
{
    Booster *b = new Booster;
    if (b && b->initBooster(bType, xPos)) {
        b->autorelease();
        return b;
    }   else    {
        delete b;
        return NULL;
    }
}

bool Booster::initBooster(BoosterType bType, float xPos)
{
    if( !GameObject::init() )
        return false;
    
    typeBooster = bType;
    speedFalling = BOOSTER_SPEED;
    
    this->initSprite(xPos);
    
    this->schedule(schedule_selector(Booster::updatePosition));
    
    return true;
}

void Booster::initSprite(float xPos)
{
    char *sprName = new char;
    sprintf(sprName, "booster_%d.png", (int)typeBooster);
    
    sprObject = Sprite::createWithSpriteFrameName(sprName);
    sprObject->setPosition(xPos, winSize.height*1.2f);
    this->addChild(sprObject);
    
    delete sprName;
}

void Booster::updatePosition(float dt)
{
    GameObject::updatePosition(dt);
}

void Booster::removeObject()
{
    this->removeFromParentAndCleanup(true);
}