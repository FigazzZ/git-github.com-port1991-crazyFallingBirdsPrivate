//
//  BigBird.h
//  FallingBirdsGame
//
//  Created by user on 01/07/15.
//
//

#ifndef __FallingBirdsGame__BigBird__
#define __FallingBirdsGame__BigBird__

#include "cocos2d.h"
#include "Bird.h"

#define FALLING_COEFFICIENT 1.0f        //in real life it is 9.8 m/s

using namespace cocos2d;

class BigBird : public Bird {
private:
    
    float fallingCoefficient = FALLING_COEFFICIENT;
    
    virtual bool initBird(float xPos, BirdType bType);
    virtual void initSprite(float xPos);
    virtual void updatePosition(float dt);
    void changeVectorFalling(float dt);
    
public:
    
    virtual void updateSpeed();
};

#endif /* defined(__FallingBirdsGame__BigBird__) */
