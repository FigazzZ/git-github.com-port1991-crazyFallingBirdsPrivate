//
//  GameObject.h
//  FallingBirdsGame
//
//  Created by user on 24/06/15.
//
//

#ifndef __FallingBirdsGame__GameObject__
#define __FallingBirdsGame__GameObject__

#include "cocos2d.h"

using namespace cocos2d;

class GameObject : public Layer {
private:
    
public:
    
    virtual void removeObject() = 0;
    void deleteObject();
    Rect getRectObject() const  {   return sprObject->getBoundingBox(); }
    Point getPositionObject() const {   return sprObject->getPosition();    }
   
    void setRemoved()   {   _isRemoved = true;  }
    bool isRemoved() const  {   return _isRemoved;  }

protected:
        
    bool _isRemoved = false;
    float speedFalling = 0.0f;
    Vec2 vectorFalling = Vec2(0, -1);

    
    Sprite *sprObject;
    
    virtual bool init();
    virtual void initSprite(float xPos) = 0;
    void launchFalling();
    
    virtual void updatePosition(float dt);
};

#endif /* defined(__FallingBirdsGame__GameObject__) */
