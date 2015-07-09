//
//  Bullet.cpp
//  FallingBirdsGame
//
//  Created by user on 04/07/15.
//
//

#include "Bullet.h"
#include "Constants.h"

Bullet* Bullet::createBullet(Point pos, float angle)
{
    Bullet *b = new Bullet;
    if(b->initBullet(pos, angle))
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

bool Bullet::initBullet(Point pos, float angle)
{
    if( !Layer::init() )    {
        return false;
    }
    
    this->calculateScreenSize();
    
    this->initSprite(pos, angle);
    this->calculateVectorOfFlying(angle);
    
    this->schedule(schedule_selector(Bullet::updateFlying));
    
    return true;
}

void Bullet::initSprite(Point pos, float angle)
{
    sprBullet = Sprite::createWithSpriteFrameName("bullet.png");
    sprBullet->setPosition(pos.x, pos.y);
    sprBullet->setRotation(angle);
    this->addChild(sprBullet);
}

void Bullet::calculateScreenSize()
{
    leftTopPointScreen = Point(0, winSize.height);
    rightBottomPointScreen = Point(winSize.width, 0);
}

void Bullet::calculateVectorOfFlying(float angle)
{
    if (angle < -90) {
        angle = angle + 90;
        
        vectorFlying.y = 1.0f - abs(angle)/90;
        vectorFlying.x = angle/90;
    }
    else
    {
        vectorFlying.x = 1.0f - abs(angle)/90;
        vectorFlying.y = abs(angle)/90;
    }
    
    vectorFlying.normalize();
}

void Bullet::utilizeBulletIfFlewAway()
{
    if(sprBullet->getPositionX() < -sprBullet->getBoundingBox().size.width*0.5f ||
       sprBullet->getPositionX() > winSize.width + sprBullet->getBoundingBox().size.width*0.5f ||
       sprBullet->getPositionY() < -sprBullet->getBoundingBox().size.width*0.5f ||
       sprBullet->getPositionY() > winSize.height + sprBullet->getBoundingBox().size.width*0.5f)
    {
        this->deleteBullet();
    }
}

void Bullet::updateFlying(float dt)
{
    if (singleton->isPaused() || singleton->isGameOver()) {
        return;
    }
    
    sprBullet->setPosition(sprBullet->getPositionX() + BULLET_SPEED * vectorFlying.x,
                           sprBullet->getPositionY() + BULLET_SPEED * vectorFlying.y);
    
    this->utilizeBulletIfFlewAway();
}

void Bullet::removeBullet()
{
    sprBullet->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f),
                                     CallFunc::create(std::bind(&Bullet::deleteBullet, this)), NULL));
}

void Bullet::deleteBullet()
{
    this->unschedule(schedule_selector(Bullet::updateFlying));
    this->removeFromParentAndCleanup(true);
}