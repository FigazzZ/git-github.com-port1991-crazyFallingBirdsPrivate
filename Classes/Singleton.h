//
//  Singleton.h
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#ifndef __FallingBirdsGame__Singleton__
#define __FallingBirdsGame__Singleton__

#include "cocos2d.h"
#include "ZFTimer.h"

#define DEFAULT_BIRD_SPEED 5.0f
#define DEFAULT_BIG_BIRD_SPEED 20.0f

#define SLOWING_BIRD_SPEED 2.0f
#define MAX_LIVES 3

#define COINS_KEY "kCoins"
#define SDK_NUMBER_KEY "kSDKNumber"
#define REMOVE_ADS_KEY "kRemoveAds"
#define SOUNDS_KEY "kSounds"
#define FIRST_INIT_KEY "kFirstInit"

using namespace cocos2d;
using namespace std;

class Bird;

enum class BoosterType  {
    Life,
    SlowBirds,
    KillBirds,
    MAX_VALUE
};

enum class SoundType    {
    MainMenuMusic,
    MissedShot,
    HitTheBird,
    PickLife,
    SlowDown,
    Boom
};

class Singleton : public Ref {
private:
    static Singleton* theSingleInstance;
    
    UserDefault* defaults;
    int lives = 1;
    int gameScore = 0;
    bool _isGameOver = false;
    bool _isPaused = false;
    
    float birdSpeed = DEFAULT_BIRD_SPEED;
    float speedyBirdSpeed = DEFAULT_BIRD_SPEED * 2.0f;
    float bigBirdSpeed = DEFAULT_BIG_BIRD_SPEED;
    
    ZFTimer *boosterTimer;
    
    Singleton(){};
    Singleton(const Singleton& root);
    Singleton& operator=(const Singleton&);
    
    void initUserDefaults();
    void firstInit();
    void initBoosterTimer();
    void removeSpeedBooster(vector<Bird*>* birdsVector, float prevRegBirdSpeed, float prevSpeedyBirdSpeed, float prevBigBirdSpeed);
    
public:
    
    static Singleton* getInstance();
    
    void collectBird();
    int getGameScore() const    {   return gameScore;   }
    
    void setGameOver()  {   _isGameOver = true;  }
    bool isGameOver() const {   return _isGameOver; }
    
    void setPaused(bool value);
    bool isPaused() const   {   return _isPaused;   }
    
    void increaseBirdSpeed();  //kind of tricky feature. If increasing speed was while speed booster is activated, increasing of speed will be more lower.
    float getBirdSpeed() const  {   return birdSpeed;   }
    float getSpeedyBirdSpeed() const    {   return speedyBirdSpeed; }
    float getBigBirdSpeed() const   {   return bigBirdSpeed;    }
    
    void slowBirdSpeed(vector<Bird*>* birdsVector);
    
    void saveCoins();
    int getCoins() const;
    void refreshGameConditions();
    
    //sounds
    void playSound(SoundType sType);
    void setSound(bool value);
    bool isSound() const;
    void changeBackgroundMusicVolume(float volume);
    void stopSound();
    
    //boosters
    void addLife();
    void reduceLife();
    int getLives() const    {   return lives;   }
    bool isLivesFull();
    
    //game center
    void loginGameCenter();
    void showLeaderboard();
    void postCurrentScore();
    
    //advertising
    void showAds();
    void showApplovinBanner();
    void showChartboostBanner();
    
    //store manager
    void buyRemoveAds();
    void setRemoveAds();
    bool isAdsRemoved() const;
    void restorePurchases();
    
    void pauseTimerIfNeeded();
    void unpauseTimerIfNeeded();
};

#endif /* defined(__FallingBirdsGame__Singleton__) */
