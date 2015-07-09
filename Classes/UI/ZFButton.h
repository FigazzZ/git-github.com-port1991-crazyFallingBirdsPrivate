//
//  MenuItemImageScaled.h
//  HelloCpp
//
//  Created by Andriy Prosekov on 8/15/14.
//
//

#ifndef __HelloCpp__MenuItemImageScaled__
#define __HelloCpp__MenuItemImageScaled__

#include "cocos2d.h"

using namespace cocos2d;

class ZFButton : public MenuItemSprite
{
private:
    bool isActivated = false;
    ParticleFire *highlightParticle = NULL;
    
    float scaleCoeff = 1.0f;    float highlightCoef = 1.0f;
    bool isMaxHintScale = false;
    bool isSwitched = false;
    
    
    void selected();
    void unselected();
    
    void handleHighlighting(float dt);
    CC_DISALLOW_COPY_AND_ASSIGN(ZFButton);
public:
    ZFButton(){}
    virtual ~ZFButton() {}
    void hitchBow();
    void hitchLock();
    static ZFButton* createWithFile(const std::string &normalImage, const std::string &selectedImage, const ccMenuCallback& callback);
    static ZFButton* createWithSpriteFrame(const std::string &normalImage, const std::string &selectedImage, const ccMenuCallback& callback);
    bool initWithNormalSprite(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, const ccMenuCallback& selector)    {
        return MenuItemSprite::initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, selector);
    }
    void getActivatedButton();
    void deactivateButton();
    void highlightButton();
    void switchImages();
    void setScaleCoefficient(float scale);
};

#endif /* defined(__HelloCpp__MenuItemImageScaled__) */
