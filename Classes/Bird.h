//
//  FallingBird.h
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#ifndef __FallingBirdsGame__Bird__
#define __FallingBirdsGame__Bird__

#include "GameObject.h"
#include "Constants.h"

#define BIRD_DEATH_FRAMES 8

enum class BirdType
{
    REGULAR_BIRD,
    SPEEDY_BIRD,
    BIG_BIRD,
    MAX
};

class Bird : public GameObject {
protected:
    
    BirdType birdType;
    
    bool _passed = false;
    
    virtual bool initBird(float xPos, BirdType bType);
    virtual void initSprite(float xPos);
    void showDeathAnimation();
    
    virtual void updatePosition(float dt);
    
public:
    
    static Bird* createBird(float xPos, BirdType bType);
    
    virtual void updateSpeed();
    virtual void removeObject();
        
    bool passed()   const   {   return _passed; }
    
};

#endif /* defined(__FallingBirdsGame__FallingBird__) */
