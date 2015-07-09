//
//  MachineGuns.h
//  FallingBirdsGame
//
//  Created by user on 04/07/15.
//
//

#ifndef __FallingBirdsGame__MachineGuns__
#define __FallingBirdsGame__MachineGuns__

#include "cocos2d.h"

using namespace cocos2d;

class MachineGuns : public Layer {
private:
    
    Point directionPoint;
    
    Layer *machinesLayer;
    Layer *bulletsLayer;
    
    Sprite *leftGun;
    Sprite *sprLeftShooting;
    Sprite *rightGun;
    Sprite *sprRightShooting;
    
    bool initMachineGuns();
    void initGuns();
    
    void storeShootingAnimation();
    void startShootingAnimation();
    void endShootingAnimation();
    void reboundGuns(cocos2d::Vec2 leftReverseVector, cocos2d::Vec2 rightReverseVector);
    
    float getAngleBtw2Vectors(cocos2d::Vec2 v1, cocos2d::Vec2 v2);

    void updateShooting(float dt);
    
public:
    
    static MachineGuns* createMachineGuns();

    void showMachineGuns();
    void hideMachineGuns();
    
    void startShooting();
    void endShooting();
    
    void directGuns(Point p);
    
    Vector<cocos2d::Node*> getBullets() const    {   return bulletsLayer->getChildren(); }
};

#endif /* defined(__FallingBirdsGame__MachineGuns__) */
