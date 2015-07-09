//
//  TutorialScreen.cpp
//  FallingBirdsGame
//
//  Created by user on 29/06/15.
//
//

#include "TutorialScreen.h"
#include "Constants.h"
#include "ZFLabel.h"
#include "ZFButton.h"

TutorialScreen* TutorialScreen::createTutorialLayer()
{
    TutorialScreen *ts = new TutorialScreen;
    
    if(ts && ts->initTutorialLayer())
    {
        ts->autorelease();
        return ts;
    }   else    {
        delete ts;
        return NULL;
    }
}

bool TutorialScreen::initTutorialLayer()
{
    if( !Layer::init() )    {
        return false;
    }
    
    interfaceLayer = Layer::create();
    interfaceLayer->setCascadeOpacityEnabled(true);
    this->addChild(interfaceLayer, 1);
    
    this->initBackground();
    this->initButtonBack();
    this->initExplanation();
    
    return true;
}

void TutorialScreen::initBackground()
{
    Sprite *sprBackground = Sprite::create("mainMenuBack.png");
    sprBackground->setPosition(winSize.width*0.5, winSize.height*0.5);
    this->addChild(sprBackground);
}

void TutorialScreen::initButtonBack()
{
    ZFButton *backButton = ZFButton::createWithFile("btnBack.png",
                                                    "btnBack.png",
                                                    std::bind(&TutorialScreen::backPressed, this));
    backButton->setPosition(winSize.width*0.08, winSize.height*0.08);
    
    btnsMenu = Menu::create(backButton, NULL);
    btnsMenu->setPosition(Point::ZERO);
    interfaceLayer->addChild(btnsMenu);
}

void TutorialScreen::initExplanation()
{
    this->explanationBooster0();
    this->explanationBooster1();
    this->explanationBooster2();
}

void TutorialScreen::explanationBooster0()
{
    Sprite *sprBooster0 = Sprite::createWithSpriteFrameName("booster_0.png");
    sprBooster0->setPosition(winSize.width*0.2, winSize.height*0.8);
    sprBooster0->setScale(2.0f);
    interfaceLayer->addChild(sprBooster0);
    
    ZFLabel *labelExplanation0 = ZFLabel::createWithTTF("Take it and you can miss one bird. But you shouldn't :)",
                                                        "ObelixPro.TTF",
                                                        70,
                                                        labelShadow);
    labelExplanation0->setPosition(winSize.width*0.6, winSize.height*0.8);
    labelExplanation0->setLineSize(winSize.width*0.4);
    labelExplanation0->setColor(Color3B::WHITE);
    interfaceLayer->addChild(labelExplanation0);
}

void TutorialScreen::explanationBooster1()
{
    Sprite *sprBooster1 = Sprite::createWithSpriteFrameName("booster_1.png");
    sprBooster1->setPosition(winSize.width*0.2, winSize.height*0.5);
    sprBooster1->setScale(2.0f);
    interfaceLayer->addChild(sprBooster1);
    
    ZFLabel *labelExplanation1 = ZFLabel::createWithTTF("Take it and birds will be veryyyy sloooow...",
                                                        "ObelixPro.TTF",
                                                        70,
                                                        labelShadow);
    labelExplanation1->setPosition(winSize.width*0.6, winSize.height*0.5);
    labelExplanation1->setLineSize(winSize.width*0.4);
    labelExplanation1->setColor(Color3B::WHITE);
    interfaceLayer->addChild(labelExplanation1);
}

void TutorialScreen::explanationBooster2()
{
    Sprite *sprBooster2 = Sprite::createWithSpriteFrameName("booster_2.png");
    sprBooster2->setPosition(winSize.width*0.2, winSize.height*0.2);
    sprBooster2->setScale(2.0f);
    interfaceLayer->addChild(sprBooster2);
    
    ZFLabel *labelExplanation2 = ZFLabel::createWithTTF("Take it and it will kill all birds!",
                                                        "ObelixPro.TTF",
                                                        70,
                                                        labelShadow);
    labelExplanation2->setPosition(winSize.width*0.6, winSize.height*0.2);
    labelExplanation2->setLineSize(winSize.width*0.4);
    labelExplanation2->setColor(Color3B::WHITE);
    interfaceLayer->addChild(labelExplanation2);
}

void TutorialScreen::hideTurorialLayer()
{
    this->setVisible(false);
    /*this->runAction(Sequence::create(CallFunc::create(std::bind(&Menu::setEnabled, btnsMenu, false)),
                                     CallFunc::create(std::bind(&TutorialScreen::removeInterface, this)),
                                     DelayTime::create(0.4f),
                                     CallFunc::create(std::bind(&TutorialScreen::setVisible, this, false)),
                                     CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 255)),
                                     CallFunc::create(std::bind(&Menu::setEnabled, btnsMenu, true)),
                                     NULL));*/
}

void TutorialScreen::removeInterface()
{
    interfaceLayer->setOpacity(100);
    interfaceLayer->runAction(Sequence::create(CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 100)),
                                               DelayTime::create(0.05f),
                                               CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 255)),
                                               DelayTime::create(0.05f),
                                               CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 100)),
                                               DelayTime::create(0.05f),
                                               CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 255)),
                                               DelayTime::create(0.05f),
                                               CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 0)),
                                               NULL));
}

void TutorialScreen::backPressed()
{
    this->hideTurorialLayer();
}
