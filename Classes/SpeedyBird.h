//
//  SpeedyBird.h
//  FallingBirdsGame
//
//  Created by user on 30/06/15.
//
//

#ifndef __FallingBirdsGame__SpeedyBird__
#define __FallingBirdsGame__SpeedyBird__

#include "cocos2d.h"
#include "Bird.h"

using namespace cocos2d;

class SpeedyBird : public Bird {
private:
    
    
    virtual bool initBird(float xPos, BirdType bType);
    
    virtual void updatePosition(float dt);
    
public:

    virtual void updateSpeed();
};

#endif /* defined(__FallingBirdsGame__SpeedyBird__) */
