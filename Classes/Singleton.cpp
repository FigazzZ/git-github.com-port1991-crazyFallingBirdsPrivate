//
//  Singleton.cpp
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#include "Singleton.h"
#include "GameCenter.h"
#include "Bird.h"
#include "SpeedyBird.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

Singleton* Singleton::theSingleInstance = NULL;

Singleton* Singleton::getInstance()
{
    if(!theSingleInstance)  {
        theSingleInstance = new Singleton();
        theSingleInstance->initBoosterTimer();
        theSingleInstance->initUserDefaults();
        theSingleInstance->firstInit();
    }
    
    return theSingleInstance;
}

void Singleton::initUserDefaults()
{
    defaults = UserDefault::getInstance();
}

void Singleton::firstInit()
{
    if(!defaults->getBoolForKey(FIRST_INIT_KEY, false))
    {
        defaults->setBoolForKey(FIRST_INIT_KEY, true);
        this->setSound(true);
    }
}

void Singleton::initBoosterTimer()
{
    boosterTimer = new ZFTimer();
}

void Singleton::collectBird()
{
    gameScore++;
}

void Singleton::saveCoins()
{
    int oldScore = this->getCoins();
    int newScore = oldScore + gameScore;
    
    defaults->setIntegerForKey(COINS_KEY, newScore);
}

int Singleton::getCoins() const
{
    return defaults->getIntegerForKey(COINS_KEY);
}

void Singleton::refreshGameConditions()
{
    _isGameOver = false;
    _isPaused = false;
    gameScore = 0;
    lives = 1;
    birdSpeed = DEFAULT_BIRD_SPEED;
    speedyBirdSpeed = DEFAULT_BIRD_SPEED*2.0f;
}

void Singleton::addLife()
{
    lives++;
}

void Singleton::reduceLife()
{
    lives--;
}

bool Singleton::isLivesFull()
{
    if (lives == MAX_LIVES) {
        return true;
    }   else    {
        return false;
    }
}

void Singleton::increaseBirdSpeed()
{
    birdSpeed += birdSpeed*0.2f;
    speedyBirdSpeed += birdSpeed*0.3f;
}

void Singleton::slowBirdSpeed(vector<Bird *> *birdsVector)
{
    boosterTimer->launchTimer(4.0f, std::bind(&Singleton::removeSpeedBooster,
                                              theSingleInstance,
                                              birdsVector,
                                              birdSpeed,
                                              speedyBirdSpeed,
                                              bigBirdSpeed));
    
    birdSpeed = SLOWING_BIRD_SPEED;
    speedyBirdSpeed = SLOWING_BIRD_SPEED;
    bigBirdSpeed = SLOWING_BIRD_SPEED;
    
    
    for (int i = 0; i < birdsVector->size(); i++) {
        birdsVector->at(i)->updateSpeed();
    }
}

void Singleton::removeSpeedBooster(vector<Bird *> *birdsVector,
                                   float prevRegBirdSpeed, float prevSpeedyBirdSpeed, float prevBigBirdSpeed)
{
    birdSpeed -= SLOWING_BIRD_SPEED;
    birdSpeed += prevRegBirdSpeed; //because if the slow down booster is activated and user can get through speed increasing barrier, result was saved after restoring normal speed
    speedyBirdSpeed -= SLOWING_BIRD_SPEED;
    speedyBirdSpeed += prevSpeedyBirdSpeed;
    bigBirdSpeed = DEFAULT_BIG_BIRD_SPEED;
    
    for (int i = 0; i < birdsVector->size(); i++) {
        birdsVector->at(i)->updateSpeed();
    }
}

void Singleton::playSound(SoundType sType)
{
    if(!this->isSound())
        return;
    
    switch (sType) {
        case SoundType::MainMenuMusic:
        {
            SimpleAudioEngine::getInstance()->playBackgroundMusic("mainMusic.mp3", true);
        }
            break;
        case SoundType::MissedShot:
        {
            SimpleAudioEngine::getInstance()->playEffect("missingShotgun.mp3", false, 1.0, 1.0, 0.6);
        }
            break;
        case SoundType::HitTheBird:
        {
            SimpleAudioEngine::getInstance()->playEffect("shotgunHitBird.mp3", false, 1.0, 1.0, 0.6);
        }
            break;
        case SoundType::PickLife:
        {
            SimpleAudioEngine::getInstance()->playEffect("pickLife.mp3");
        }
            break;
        case SoundType::SlowDown:
        {
            SimpleAudioEngine::getInstance()->playEffect("slowDown.mp3");
        }
            break;
        case SoundType::Boom:
        {
            SimpleAudioEngine::getInstance()->playEffect("boomBonus.mp3");
        }
            break;
        default:
            break;
    }
}

void Singleton::setSound(bool value)
{
    defaults->setBoolForKey(SOUNDS_KEY, value);
}

bool Singleton::isSound() const
{
    return defaults->getBoolForKey(SOUNDS_KEY);
}

void Singleton::stopSound()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Singleton::changeBackgroundMusicVolume(float volume)
{
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

void Singleton::setPaused(bool value)
{
    _isPaused = value;
    
    if (boosterTimer->ifTimerHasTask()) {
        if(_isPaused)
        {
            boosterTimer->pauseTimer();
        }
        else
        {
            boosterTimer->resumeTimer();
        }
    }
}

void Singleton::pauseTimerIfNeeded()
{
    if(boosterTimer->ifTimerHasTask())
        boosterTimer->pauseTimer();
}

void Singleton::unpauseTimerIfNeeded()
{
    if(boosterTimer->ifTimerHasTask())
        boosterTimer->resumeTimer();
}

void Singleton::loginGameCenter()
{
    avalon::GameCenter *gm;
    gm->login();
}

void Singleton::showLeaderboard()
{
    avalon::GameCenter *gm;
    gm->login();
    gm->showScores();
}

void Singleton::postCurrentScore()
{
    if(gameScore > 0)   {
        avalon::GameCenter *gm;
        gm->postScore("com.portgames.crazyfallingbirds.leaderboard", gameScore);
    }
}