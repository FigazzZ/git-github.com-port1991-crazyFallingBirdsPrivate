//
//  MenuItemImageScaled.cpp
//  HelloCpp
//
//  Created by Andriy Prosekov on 8/15/14.
//
//

#include "ZFButton.h"

ZFButton* ZFButton::createWithFile(const std::string &normalImage, const std::string &selectedImage, const ccMenuCallback &callback)
{
    ZFButton *ret = new ZFButton();
    
    Sprite *normalSprite = Sprite::create(normalImage);
    Sprite *selectedSprite = Sprite::create(selectedImage);
    
    if (ret && ret->initWithNormalSprite(normalSprite, selectedSprite, nullptr, callback))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

ZFButton* ZFButton::createWithSpriteFrame(const std::string &normalImage, const std::string &selectedImage, const ccMenuCallback &callback)
{
    ZFButton *ret = new ZFButton();
    
    Sprite *normalSprite = Sprite::createWithSpriteFrameName(normalImage);
    Sprite *selectedSprite = Sprite::createWithSpriteFrameName(selectedImage);
    
    if (ret && ret->initWithNormalSprite(normalSprite, selectedSprite, nullptr, callback))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void ZFButton::selected()
{
    MenuItemSprite::selected();
   
    _actionManager->pauseTarget(this);

    ScaleTo *scale1 = ScaleTo::create(0.1f, scaleCoeff * 0.95f);
    ScaleTo *scale2 = ScaleTo::create(0.09f, scaleCoeff * 0.97f);
    EaseBackInOut *ease2 = EaseBackInOut::create(scale2);
    
    this->runAction(Sequence::create(scale1, ease2, CallFunc::create(std::bind(&ActionManager::resumeTarget, _actionManager, this)), NULL));
}

void ZFButton::unselected()
{
    MenuItemSprite::unselected();
   
    _actionManager->resumeTarget(this);
    
    ScaleTo *scale1 = ScaleTo::create(0.09f, scaleCoeff * 1.02f);
    ScaleTo *scale2 = ScaleTo::create(0.07f, scaleCoeff * 0.97f);
    ScaleTo *scale3 = ScaleTo::create(0.1f, scaleCoeff * 1.0f);
    EaseBackIn *ease3 = EaseBackIn::create(scale3);
    
    this->runAction(Sequence::create(scale1, scale2, ease3, CallFunc::create(std::bind(&ActionManager::resumeTarget, _actionManager, this)), NULL));
}

void ZFButton::hitchBow()
{
    Sprite *sprBow = Sprite::create("bow.png");
    sprBow->setPosition(this->getBoundingBox().size.width*0.1, this->getBoundingBox().size.height*0.06);
    this->addChild(sprBow);
    
    RotateTo *rotate0 = RotateTo::create(0.1, 5);
    RotateTo *rotate1 = RotateTo::create(0.2, -5);
    RotateTo *rotate2 = RotateTo::create(0.2, 5);
    RotateTo *rotate3 = RotateTo::create(0.2, -5);
    RotateTo *rotate4 = RotateTo::create(0.2, 0);
    DelayTime *delay = DelayTime::create(4.0f);
    
    Sequence *rotateSequence = Sequence::create(rotate0, rotate1, rotate2, rotate3, rotate4, delay, NULL);
    sprBow->runAction(RepeatForever::create(rotateSequence));
}

void ZFButton::hitchLock()
{
    Sprite *sprLock = Sprite::create("lock.png");
    sprLock->setPosition(this->getBoundingBox().size.width*0.17, this->getBoundingBox().size.height*0.8);
    this->addChild(sprLock);
    
    sprLock->setAnchorPoint(Vec2(0.5, 1.0));
    RotateTo *left = RotateTo::create(2.5f, -10);
    EaseInOut *easeLeft = EaseInOut::create(left, 3.0);
    RotateTo *right = RotateTo::create(2.5f, 10);
    EaseInOut *easeRight = EaseInOut::create(right, 3.0);
    Sequence *rotateSeq = Sequence::create(easeLeft, easeRight, NULL);
    
    
    sprLock->runAction(RepeatForever::create(rotateSeq));
    
}

void ZFButton::getActivatedButton()
{
    isActivated = true;
    MenuItemSprite::selected();
    
    ScaleTo *scale1 = ScaleTo::create(2.0f, 0.95f);
    ScaleTo *scale2 = ScaleTo::create(2.0f, 1.05f);
    
    Sequence *seqScale = Sequence::create(scale1, scale2, NULL);
    this->runAction(RepeatForever::create(seqScale));
    
     if(highlightParticle != NULL)
    {
        highlightParticle->removeFromParentAndCleanup(true);
        highlightParticle = NULL;
    }
    
    highlightParticle = ParticleFire::createWithTotalParticles(120);
    highlightParticle->setPosition(this->getBoundingBox().size.width*0.5, this->getBoundingBox().size.height*0.05);
    highlightParticle->setPosVar(Vec2(this->getBoundingBox().size.width*0.45 , 0));
    this->addChild(highlightParticle, 10);
}

void ZFButton::deactivateButton()
{
    if(isActivated)
    {
        this->stopAllActions();
        this->unselected();
        this->runAction(ScaleTo::create(0.1f, 1.0f));
        
        highlightParticle->stopSystem();
    }
}

void ZFButton::highlightButton()
{
    GLProgram *p = GLProgram::createWithFilenames("Base.vsh", "Highlight.fsh");
    this->getNormalImage()->setGLProgram(p);
    this->setOnExitCallback([&]{
        this->getNormalImage()->getGLProgram()->~GLProgram();        
    });
    this->schedule(schedule_selector(ZFButton::handleHighlighting), 0.03f);
}

void ZFButton::handleHighlighting(float dt)
{
        
    if (isMaxHintScale)
    {
        highlightCoef -= 0.009;
        if (highlightCoef < 1.0)
        {
            isMaxHintScale = false;
        }
    }
    else
    {
        highlightCoef += 0.009;
        if (highlightCoef > 1.2)
        {
            isMaxHintScale = true;
        }
    }
   // this->setScale(highlightCoef);
    float shaderCoef = (highlightCoef - 1) * 1.6;
    
    this->getNormalImage()->getGLProgram()->updateUniforms();
    
    uint locationForShader = this->getNormalImage()->getGLProgram()->getUniformLocation("u_colorCoef");
    glUniform1f(locationForShader, shaderCoef);
}

void ZFButton::switchImages()
{
    this->stopAllActions();
    this->getNormalImage()->getGLProgram()->~GLProgram();
    if(!isSwitched)
    {
        MenuItemSprite::selected();
    }
    else
    {
        MenuItemSprite::unselected();
    }
    
    isSwitched = !isSwitched;
}

void ZFButton::setScaleCoefficient(float scale)
{
    scaleCoeff = scale;
    this->setScale(scale);
}
