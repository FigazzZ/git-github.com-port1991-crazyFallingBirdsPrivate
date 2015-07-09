//
//  Booster.h
//  FallingBirdsGame
//
//  Created by user on 24/06/15.
//
//

#ifndef __FallingBirdsGame__Booster__
#define __FallingBirdsGame__Booster__

#include "GameObject.h"
#include "Constants.h"

#define BOOSTER_SPEED 2.0f

class Booster : public GameObject {

private:
    
    BoosterType typeBooster;
    
    //methods
    bool initBooster(BoosterType bType, float xPos);
    
    virtual void initSprite(float xPos);
    virtual void updatePosition(float dt);
    
public:
    
    static Booster* createBooster(BoosterType bType, float xPos);
    
    BoosterType getBoosterType() const  {   return typeBooster; }
    virtual void removeObject();
};

#endif /* defined(__FallingBirdsGame__Booster__) */
