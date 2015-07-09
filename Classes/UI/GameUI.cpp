//
//  GameUI.cpp
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#include "GameUI.h"
#include "Constants.h"
#include "MainMenu.h"
#include "GameScene.h"
#define SHRAPNEL_COUNT_FRAMES 9

GameUI* GameUI::createUserInterface()
{
    GameUI *gu = new GameUI;
    if (gu->initUserInterface()) {
        gu->autorelease();
        return gu;
    }
    else    {
        delete gu;
        return NULL;
    }
}

bool GameUI::initUserInterface()
{
    if( !Layer::init() )
        return false;
    
    menuLayer = Layer::create();
    menuLayer->setPosition(Point::ZERO);
    this->addChild(menuLayer, 1);
    
    this->initDefaultInterface();
    this->initLivesPanel();
    
    return true;
}

void GameUI::initDefaultInterface()
{
    btnPause = ZFButton::createWithFile("btnPause.png",
                                        "btnPause.png",
                                        std::bind(&GameUI::pauseGame, this));
    btnPause->setPosition(winSize.width*0.92, winSize.height*0.92);
    btnPause->setOpacity(120);
    
    Menu* btnsMenu = Menu::create(btnPause, NULL);
    btnsMenu->setPosition(Point::ZERO);
    this->addChild(btnsMenu);
    
    labelScore = ZFLabel::createWithTTF(to_string(singleton->getGameScore()), "ObelixPro.TTF", 60, labelRegular);
    labelScore->setPosition(winSize.width*0.15, winSize.height*0.92);
    labelScore->setColor(Color3B::BLACK);
    this->addChild(labelScore);
}

void GameUI::initLivesPanel()
{
    float offSetX = 0.0f;
    for (int i = 0; i < singleton->getLives(); i++) {
        Sprite *sprLife = Sprite::createWithSpriteFrameName("booster_0.png");
        sprLife->setScale(0.6f);
        sprLife->setPosition(winSize.width*0.4 + offSetX, winSize.height*0.93);
        this->addChild(sprLife);
        offSetX += sprLife->getBoundingBox().size.width*1.1f;
        
        stackLives.push(sprLife);
    }
}

void GameUI::initWhiteFade()
{
    whiteFade = Sprite::create("fadeWhite.png");
    whiteFade->setPosition(winSize.width*0.5, winSize.height*0.5);
    whiteFade->setScale(winSize.width, winSize.height);
    this->addChild(whiteFade, 3);
    whiteFade->setOpacity(0);
}

void GameUI::addLife()
{
    Sprite *sprLife = Sprite::createWithSpriteFrameName("booster_0.png");
    sprLife->setScale(0.6f);
    sprLife->setPosition(stackLives.top()->getPositionX() + sprLife->getBoundingBox().size.width*1.1f, winSize.height*0.93);
    this->addChild(sprLife);
    
    stackLives.push(sprLife);
}

void GameUI::reduceLife()
{
    stackLives.top()->removeFromParentAndCleanup(true);
    stackLives.pop();
}

void GameUI::pauseGame()
{
    singleton->setPaused(true);
    this->showPauseScreen();
    btnPause->setEnabled(false);
}

void GameUI::showPauseScreen()
{
    Sprite *fadeTexture = Sprite::create("fadeBack.png");
    fadeTexture->setPosition(winSize.width*0.5, winSize.height*0.5);
    fadeTexture->setScale(winSize.width, winSize.height);
    menuLayer->addChild(fadeTexture);
    fadeTexture->setOpacity(160);
    
    Sprite *sprLogo = Sprite::create("PauseLogo.png");
    sprLogo->setPosition(winSize.width*0.5, winSize.height*0.7);
    menuLayer->addChild(sprLogo);
    
    ZFButton *btnMainMenu = ZFButton::createWithFile("Button-Home.png",
                                                     "Button-Home.png",
                                                     std::bind(&GameUI::goMainMenu, this));
    btnMainMenu->setPosition(winSize.width*0.3, winSize.height*0.4);
    
    ZFButton *btnRetry = ZFButton::createWithFile("Button-Restart.png",
                                                  "Button-Restart.png",
                                                  std::bind(&GameUI::restartGame, this));
    btnRetry->setPosition(winSize.width*0.5, winSize.height*0.4);
    
    ZFButton *btnContinue = ZFButton::createWithFile("Button-Continue.png",
                                                     "Button-Continue.png",
                                                     std::bind(&GameUI::continueGame, this));
    btnContinue->setPosition(winSize.width*0.7, winSize.height*0.4);
    
    Menu *btnsMenu = Menu::create(btnMainMenu, btnRetry, btnContinue, NULL);
    btnsMenu->setPosition(Point::ZERO);
    menuLayer->addChild(btnsMenu);
}

void GameUI::clearPauseScreen()
{
    menuLayer->removeAllChildren();
}

void GameUI::goMainMenu()
{
    singleton->refreshGameConditions();
    
    Scene *mainMenuScene = MainMenu::create();
    mainMenuScene = TransitionFade::create(0.6f, mainMenuScene, Color3B::WHITE);
    Director::getInstance()->replaceScene(mainMenuScene);
}

void GameUI::restartGame()
{
    singleton->refreshGameConditions();
    
    Scene *gameScene = GameScene::create();
    Director::getInstance()->replaceScene(gameScene);
}

void GameUI::continueGame()
{
    singleton->setPaused(false);
    this->clearPauseScreen();
    btnPause->setEnabled(true);
}

void GameUI::showGameOver()
{
    if(singleton->isPaused())
    {
        this->clearPauseScreen();
    }
    
    btnPause->setEnabled(false);
    
    Sprite *fadeTexture = Sprite::create("fadeBack.png");
    fadeTexture->setPosition(winSize.width*0.5, winSize.height*0.5);
    fadeTexture->setScale(winSize.width, winSize.height);
    this->addChild(fadeTexture);
    fadeTexture->setOpacity(160);
    
    //ZFLabel *labelGameOver = ZFLabel::createWithTTF("GAME OVER", "ObelixPro.TTF", 120, labelRegular);
    //labelGameOver->setPosition(winSize.width*0.5, winSize.height*0.75);
    //this->addChild(labelGameOver);
    
    Sprite *sprGameOver = Sprite::create("GameOverLogo.png");
    sprGameOver->setPosition(winSize.width*0.5, winSize.height*0.75);
    this->addChild(sprGameOver);
    
    sprGameOver->setScale(0.0f);
    sprGameOver->runAction(Sequence::create(DelayTime::create(0.2f),
                                            EaseBackOut::create(ScaleTo::create(0.6f, 1.0f)), NULL));
    
    char scoreChar[100];
    sprintf(scoreChar, "YOUR SCORE IS: %d", singleton->getGameScore());
    
    ZFLabel *labelScore = ZFLabel::createWithTTF(scoreChar, "ObelixPro.TTF", 80, labelRegular);
    labelScore->setPosition(winSize.width*0.5, winSize.height*0.5);
    this->addChild(labelScore);
    
    labelScore->setScale(0.0f);
    labelScore->runAction(Sequence::create(DelayTime::create(0.9f),
                                           EaseBackOut::create(ScaleTo::create(0.6f, 1.0f)), NULL));
    
    
    ZFButton *btnMainMenu = ZFButton::createWithFile("Button-Home.png",
                                                     "Button-Home.png",
                                                     std::bind(&GameUI::goMainMenu, this));
    btnMainMenu->setPosition(winSize.width*0.4, winSize.height*0.35);
    
    ZFButton *btnRetry = ZFButton::createWithFile("Button-Restart.png",
                                                  "Button-Restart.png",
                                                  std::bind(&GameUI::restartGame, this));
    btnRetry->setPosition(winSize.width*0.6, winSize.height*0.35);
    
    Menu *btnsMenu = Menu::create(btnMainMenu, btnRetry, NULL);
    btnsMenu->setPosition(Point::ZERO);
    this->addChild(btnsMenu);
}

void GameUI::showShrapnel(Point p)
{
    Sprite *shrapnelAnimation = Sprite::createWithSpriteFrameName("shrapnel_0.png");
    shrapnelAnimation->setPosition(p);
    this->addChild(shrapnelAnimation);
    
    Vector<SpriteFrame*> frames;
    char *frameName = new char;
    
    for (int i = 0; i < SHRAPNEL_COUNT_FRAMES; i++) {
        sprintf(frameName, "shrapnel_%d.png", i);
        SpriteFrame *frame = Sprite::createWithSpriteFrameName(frameName)->getSpriteFrame();
        frames.pushBack(frame);
    }
    delete []frameName;
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.05f);
    Animate *animate = Animate::create(animation);
    
    shrapnelAnimation->runAction(Sequence::create(Repeat::create(animate, 1),
                                                  CallFunc::create(std::bind(&Sprite::removeFromParentAndCleanup,
                                                                             shrapnelAnimation, true)),
                                                  NULL));
}

void GameUI::showSparkles(Point p)
{
    ParticleSystemQuad *pSystem = ParticleSystemQuad::create("hitBullet.plist");
    pSystem->setPosition(p);
    this->addChild(pSystem);
    pSystem->setAutoRemoveOnFinish(true);
    pSystem->setBlendAdditive(false);
}

void GameUI::showBombEffect()
{
    whiteFade->setOpacity(230);
    
    whiteFade->runAction(FadeOut::create(0.6f));
}

void GameUI::updateLabelScore()
{
    labelScore->changeString(to_string(singleton->getGameScore()));
}