//
//  MainMenu.cpp
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#include "MainMenu.h"
#include "Constants.h"
#include "GameScene.h"

bool MainMenu::init()
{
    if (!Scene::init())
        return false;
    
    interfaceLayer = Layer::create();
    interfaceLayer->setCascadeOpacityEnabled(true);
    this->addChild(interfaceLayer, 1);
    
    tutorialLayer = Layer::create();
    this->addChild(tutorialLayer, 2);
    
    this->initBackground();
    this->initButtons();
    this->initTutorialScreen();
    
    if(!singleton->isAdsRemoved())
        singleton->showAds();
    
    singleton->playSound(SoundType::MainMenuMusic);
    singleton->changeBackgroundMusicVolume(1.0f);
    
    return true;
}

void MainMenu::initBackground()
{
    Sprite *sprBackground = Sprite::create("mainMenuBack.png");
    sprBackground->setPosition(winSize.width*0.5, winSize.height*0.5);
    this->addChild(sprBackground);
    
    Sprite *sprLogo = Sprite::create("title.png");
    sprLogo->setPosition(winSize.width*0.5, winSize.height*0.75);
    interfaceLayer->addChild(sprLogo);
}

void MainMenu::initButtons()
{
    ZFButton *btnPlay = ZFButton::createWithFile("btnPlay.png",
                                                 "btnPlay.png",
                                                 std::bind(&MainMenu::playPressed, this));
    btnPlay->setPosition(winSize.width*0.5, winSize.height*0.48);
    
    ZFButton *btnStore = ZFButton::createWithFile("btnStore.png",
                                                  "btnStore.png",
                                                  std::bind(&MainMenu::storePressed, this));
    btnStore->setPosition(winSize.width*0.5, winSize.height*0.35);
    btnStore->setVisible(false);
    
    ZFButton *btnGameCenter = ZFButton::createWithFile("btnLeaderboard.png",
                                                       "btnLeaderboard.png",
                                                       std::bind(&MainMenu::gameCenterPressed, this));
    btnGameCenter->setPosition(winSize.width*0.5, winSize.height*0.25);
    
    MenuItemImage *btnTutorial = MenuItemImage::create("help.png",
                                                       "help-on.png",
                                                       std::bind(&MainMenu::tutorialPressed, this));
    btnTutorial->setScale(1.2f);
    btnTutorial->setPosition(winSize.width*0.08, winSize.height*0.08);
    
    char btnSoundName[20];
    if(singleton->isSound())
        sprintf(btnSoundName, "btnSounds-on.png");
    else
        sprintf(btnSoundName, "btnSounds-off.png");
    
    btnSound = ZFButton::createWithFile(btnSoundName,
                                        btnSoundName,
                                        std::bind(&MainMenu::soundPressed, this));
    btnSound->setPosition(winSize.width*0.9, winSize.height*0.1);
    
    ZFButton *btnRemoveAds = ZFButton::createWithFile("btnRemoveAds.png",
                                                      "btnRemoveAds.png",
                                                      std::bind(&MainMenu::removeAdsPressed, this));
    btnRemoveAds->setPosition(winSize.width*0.15, winSize.height*0.25);
    
    ZFButton *btnRestorePurchases = ZFButton::createWithFile("btnRestorePurchases.png",
                                                             "btnRestorePurchases.png",
                                                             std::bind(&MainMenu::restorePurchasesPressed, this));
    btnRestorePurchases->setPosition(winSize.width*0.85, winSize.height*0.25);
    
    btnsMenu = Menu::create(btnPlay, btnGameCenter, btnTutorial, btnStore, btnRemoveAds, btnRestorePurchases, btnSound, NULL);
    btnsMenu->setPosition(Point::ZERO);
    interfaceLayer->addChild(btnsMenu);
}

void MainMenu::initTutorialScreen()
{
    tScreen = TutorialScreen::createTutorialLayer();
    tScreen->setPosition(Point::ZERO);
    tutorialLayer->addChild(tScreen);
    
    tScreen->setVisible(false);
}

void MainMenu::showTutorialScreen()
{
    tScreen->setVisible(true);
}

void MainMenu::playPressed()
{
    Scene *_gameScene = GameScene::create();
    _gameScene = TransitionFade::create(0.6f, _gameScene, Color3B::WHITE);
    Director::getInstance()->replaceScene(_gameScene);
}

void MainMenu::gameCenterPressed()
{
    singleton->showLeaderboard();
}

void MainMenu::tutorialPressed()
{
    this->runAction(Sequence::create(CallFunc::create(std::bind(&Menu::setEnabled, btnsMenu, false)),
                                     CallFunc::create(std::bind(&MainMenu::removeInterface, this)),
                                     DelayTime::create(0.4f),
                                     CallFunc::create(std::bind(&Layer::setOpacity, interfaceLayer, 255)),
                                     CallFunc::create(std::bind(&MainMenu::showTutorialScreen, this)),
                                     CallFunc::create(std::bind(&Menu::setEnabled, btnsMenu, true)),
                                     NULL));
}

void MainMenu::removeAdsPressed()
{
    singleton->buyRemoveAds();
}

void MainMenu::restorePurchasesPressed()
{
    singleton->restorePurchases();
}

void MainMenu::storePressed()
{
    
}

void MainMenu::soundPressed()
{
    if (singleton->isSound()) {
        singleton->setSound(false);
        singleton->stopSound();
        btnSound->setNormalImage(Sprite::create("btnSounds-off.png"));
        btnSound->setSelectedImage(Sprite::create("btnSounds-off.png"));
    }   else    {
        singleton->setSound(true);
        singleton->playSound(SoundType::MainMenuMusic);
        btnSound->setNormalImage(Sprite::create("btnSounds-on.png"));
        btnSound->setSelectedImage(Sprite::create("btnSounds-on.png"));
    }
}

void MainMenu::removeInterface()
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
