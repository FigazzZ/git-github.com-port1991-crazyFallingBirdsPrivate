//
//  Bullet.h
//  FallingBirdsGame
//
//  Created by user on 04/07/15.
//
//

#ifndef __FallingBirdsGame__Bullet__
#define __FallingBirdsGame__Bullet__

#include "cocos2d.h"

#define BULLET_SPEED 30.0f

using namespace cocos2d;

class Bullet : public Layer {
private:
    
    Point leftTopPointScreen = Point();
    Point rightBottomPointScreen = Point();
    
    Sprite *sprBullet;
    Vec2 vectorFlying = Vec2(1, 0);
    
    bool initBullet(Point pos, float angle);
    void initSprite(Point pos, float angle);
    void calculateScreenSize();
    void calculateVectorOfFlying(float angle);
    
    void deleteBullet();
    
    void updateFlying(float dt);
    void utilizeBulletIfFlewAway();
    
public:
    static Bullet* createBullet(Point pos, float angle);
    
    void removeBullet();
    Rect getRectBullet() const  {   return sprBullet->getBoundingBox(); }
    Point getBulletPosition() const {   return sprBullet->getPosition();    }
    
    cocos2d::Vec2 getVectorFlying() const   {   return vectorFlying;    }
};

#endif /* defined(__FallingBirdsGame__Bullet__) */
