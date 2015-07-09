//
//  FallingBird.cpp
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#include "Bird.h"
#include "SpeedyBird.h"
#include "BigBird.h"

Bird* Bird::createBird(float xPos, BirdType bType)
{
    Bird *b;
    switch (bType) {
        case BirdType::REGULAR_BIRD:
        {
            b = new Bird;
        }
            break;
        case BirdType::SPEEDY_BIRD:
        {
            b = new SpeedyBird;
        }
            break;
        case BirdType::BIG_BIRD:
        {
            b = new BigBird;
        }
            break;
        default:
            break;
    }

    if( b->initBird(xPos, bType))
    {
        b->autorelease();
        return b;
    }
    else
    {
        delete b;
        return NULL;
    }
}

bool Bird::initBird(float xPos, BirdType bType)
{
    if( !GameObject::init() )
        return false;
    
    birdType = bType;
    
    this->updateSpeed();
    this->initSprite(xPos);
    this->schedule(schedule_selector(Bird::updatePosition));
    
    return true;
}

void Bird::initSprite(float xPos)
{
    char *frameName = new char;
    
    sprintf(frameName, "bird_%d_0.png", birdType);
    sprObject = Sprite::createWithSpriteFrameName(frameName);
    sprObject->setPosition(xPos, winSize.height);
    this->addChild(sprObject);
    sprObject->setRotation(90);
    
    delete []frameName;
}

void Bird::showDeathAnimation()
{
    Vector<SpriteFrame*> frames(BIRD_DEATH_FRAMES);
    char *frameName = new char;
    
    for (int i = 0; i < BIRD_DEATH_FRAMES; i++) {
        
        sprintf(frameName, "bird_%d_%d.png", birdType, i);
        SpriteFrame *frame = Sprite::createWithSpriteFrameName(frameName)->getSpriteFrame();
        frames.pushBack(frame);
    }
    
    delete []frameName;
    
    Animation *_animation = Animation::createWithSpriteFrames(frames, 0.05f);
    Animate *_animate = Animate::create(_animation);
    
    sprObject->runAction(Sequence::create(Repeat::create(_animate, 1),
                                        CallFunc::create(std::bind(&Bird::removeFromParentAndCleanup, this, true)),
                                        NULL));
}

void Bird::updatePosition(float dt)
{
    GameObject::updatePosition(dt);
    
    if(sprObject->getPositionY() < -sprObject->getBoundingBox().size.height*0.6f)   {
        _passed = true;
    }
}

void Bird::updateSpeed()
{
    speedFalling = singleton->getBirdSpeed();
}

void Bird::removeObject()
{
    this->showDeathAnimation();
}