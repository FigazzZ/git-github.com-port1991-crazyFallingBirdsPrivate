//
//  MachineGuns.cpp
//  FallingBirdsGame
//
//  Created by user on 04/07/15.
//
//

#include "MachineGuns.h"
#include "Constants.h"
#include "Bullet.h"

#define MACHINE_HEIGHT  400.0f
#define FRAMES_FIRE_ANIMATION 3
#define BULLETS_INTERVAL 0.14f

MachineGuns* MachineGuns::createMachineGuns()
{
    MachineGuns* mg = new MachineGuns;                      //надо будет сделать буловский выключатель работы пулемета, чтобы когда вдруг они прячутся, пользователь не мог стрелять
    
    if(mg->initMachineGuns())
    {
        mg->autorelease();
        return mg;
    }
    else
    {
        delete mg;
        return NULL;
    }
}

bool MachineGuns::initMachineGuns()
{
    if( !Layer::init() )    {
        return false;
    }
    
    machinesLayer = Layer::create();
    this->addChild(machinesLayer, 1);
    
    bulletsLayer = Layer::create();
    this->addChild(bulletsLayer, 1);
    
    this->initGuns();
    this->storeShootingAnimation();
    
    return true;
}

void MachineGuns::initGuns()
{
    Sprite *leftGunBase = Sprite::createWithSpriteFrameName("gun_base.png");
    leftGunBase->setPosition(winSize.width*0.06f, winSize.height*0.05f);
    machinesLayer->addChild(leftGunBase);
    
    leftGun = Sprite::createWithSpriteFrameName("gun_barrel.png");
    //leftGun->setPosition(winSize.width*0.5f, winSize.height*0.5f);
    leftGun->setPosition(winSize.width*0.035f, leftGunBase->getPositionY() + leftGun->getBoundingBox().size.height*0.7f);
    leftGun->setAnchorPoint(Vec2(0.1f, 0.6f));
    machinesLayer->addChild(leftGun);
    
    Sprite *rightGunBase = Sprite::createWithSpriteFrameName("gun_base.png");
    rightGunBase->setFlippedX(true);
    rightGunBase->setPosition(winSize.width*0.94f, winSize.height*0.05f);
    machinesLayer->addChild(rightGunBase);
    
    rightGun = Sprite::createWithSpriteFrameName("gun_barrel.png");
    rightGun->setFlippedX(true);
    rightGun->setPosition(winSize.width*0.965f, rightGunBase->getPositionY() + rightGun->getBoundingBox().size.height*0.7f);
    rightGun->setAnchorPoint(Vec2(0.9f, 0.6f));
    machinesLayer->addChild(rightGun);
    
    machinesLayer->setPosition(machinesLayer->getPositionX(), machinesLayer->getPositionY() - MACHINE_HEIGHT);
}

void MachineGuns::showMachineGuns()
{
    machinesLayer->runAction(MoveTo::create(0.7f, Point(machinesLayer->getPositionX(),
                                                        machinesLayer->getPositionY() + MACHINE_HEIGHT)));
}

void MachineGuns::hideMachineGuns()
{
    machinesLayer->runAction(MoveTo::create(0.7f, Point(machinesLayer->getPositionX(),
                                                        machinesLayer->getPositionY() - MACHINE_HEIGHT)));
}

void MachineGuns::startShooting()
{
    this->startShootingAnimation();
    this->updateShooting(0.0f);
    this->schedule(schedule_selector(MachineGuns::updateShooting), BULLETS_INTERVAL);
}

void MachineGuns::endShooting()
{
    this->endShootingAnimation();
    this->unschedule(schedule_selector(MachineGuns::updateShooting));
}

void MachineGuns::reboundGuns(Vec2 leftReverseVector, Vec2 rightReverseVector)
{
    leftGun->runAction(Sequence::create(MoveTo::create(BULLETS_INTERVAL/2.0f,
                                                       Point(leftGun->getPositionX() + 20.0f * leftReverseVector.x,
                                                                    leftGun->getPositionY() + 20.0f * leftReverseVector.y)),
                                        EaseBackOut::create(MoveTo::create(0.04f, leftGun->getPosition())), NULL));
    
    rightGun->runAction(Sequence::create(MoveTo::create(BULLETS_INTERVAL/2.0f, Point(rightGun->getPositionX() + 20.0f * rightReverseVector.x,
                                                                     rightGun->getPositionY() + 20.0f * rightReverseVector.y)),
                                         EaseBackOut::create(MoveTo::create(0.04f, rightGun->getPosition())), NULL));
}

void MachineGuns::directGuns(Point p)
{
    float leftAngle = this->getAngleBtw2Vectors(Point(1, 0),
                                                Point(p.x - leftGun->getPositionX(), p.y - leftGun->getPositionY()));
    
    if(p.y > leftGun->getPositionY())
        leftAngle *= (-1);
    
    float rightAngle = this->getAngleBtw2Vectors(Point(-1, 0),
                                                 Point(p.x - rightGun->getPositionX(), p.y - rightGun->getPositionY()));
    
    leftGun->setRotation(leftAngle);
    rightGun->setRotation(rightAngle);
    
}
                                                //сделать плавное наведение пулеметов на точку прикосновения, на паузе стопать анимацию
void MachineGuns::storeShootingAnimation()
{
    Vector<SpriteFrame*> shootingFrames;
    
    char *frameName = new char;
    for (int i = 0; i < FRAMES_FIRE_ANIMATION; i++) {
        sprintf(frameName, "fire%d.png", i);
        SpriteFrame *frame = Sprite::createWithSpriteFrameName(frameName)->getSpriteFrame();
        shootingFrames.pushBack(frame);
    }
    
    Animation *leftAnimation = Animation::createWithSpriteFrames(shootingFrames, 0.04f);
    Animate *leftAnimate = Animate::create(leftAnimation);
    
    //preparing sprites for shooting animation
    sprLeftShooting = Sprite::createWithSpriteFrameName("fire0.png");
    sprLeftShooting->setPosition(leftGun->getBoundingBox().size.width + sprLeftShooting->getBoundingBox().size.width*0.45f,
                                 leftGun->getBoundingBox().size.height*0.77f);
    leftGun->addChild(sprLeftShooting);
    sprLeftShooting->runAction(RepeatForever::create(leftAnimate));
    sprLeftShooting->setScale(0.0f);
    
    Animation *rightAnimation = Animation::createWithSpriteFrames(shootingFrames, 0.04f);
    Animate *rightAnimate = Animate::create(rightAnimation);
    
    sprRightShooting = Sprite::createWithSpriteFrameName("fire0.png");
    sprRightShooting->setFlippedX(true);
    sprRightShooting->setPosition(-sprRightShooting->getBoundingBox().size.width*0.45f,
                                  rightGun->getBoundingBox().size.height*0.77f);
    rightGun->addChild(sprRightShooting);
    sprRightShooting->runAction(RepeatForever::create(rightAnimate));
    sprRightShooting->setScale(0.0f);
}

void MachineGuns::startShootingAnimation()
{
    sprLeftShooting->setScale(1.0f);
    sprRightShooting->setScale(1.0f);
}

void MachineGuns::endShootingAnimation()
{
    sprLeftShooting->setScale(0.0f);
    sprRightShooting->setScale(0.0f);
}

float MachineGuns::getAngleBtw2Vectors(cocos2d::Vec2 v1, cocos2d::Vec2 v2)
{
    float scalarMultiplication = v1.x * v2.x + v1.y * v2.y;
    float modulev1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
    float modulev2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
    
    float cosAngle = scalarMultiplication/(modulev1*modulev2);
    float radAngle = acos(cosAngle);
    float angle = CC_RADIANS_TO_DEGREES(radAngle);
    return angle;
}

void MachineGuns::updateShooting(float dt)
{
    Point leftBulletPos = leftGun->convertToWorldSpace(sprLeftShooting->getPosition());
    float leftAngle = leftGun->getRotation();
    
    Bullet *_leftBullet = Bullet::createBullet(leftBulletPos, leftAngle);
    _leftBullet->setPosition(Point::ZERO);
    bulletsLayer->addChild(_leftBullet);
    
    Point rightBulletPos = rightGun->convertToWorldSpace(sprRightShooting->getPosition());
    float rightAngle = rightGun->getRotation() - 180;
    
    Bullet *_rightBullet = Bullet::createBullet(rightBulletPos, rightAngle);
    _rightBullet->setPosition(Point::ZERO);
    bulletsLayer->addChild(_rightBullet);
    
    this->reboundGuns(_leftBullet->getVectorFlying()*-1, _rightBullet->getVectorFlying()*-1);
}

