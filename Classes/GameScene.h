//
//  GameScene.h
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#ifndef __FallingBirdsGame__GameScene__
#define __FallingBirdsGame__GameScene__

#include "cocos2d.h"
#include "GameUI.h"
#include "Bird.h"
#include "Booster.h"
#include "SlashHandler.h"
#include "MachineGuns.h"

#define DEFAULT_LEVEL_BARRIER 8
#define DEFAULT_COOLDOWN_BIRDS 1.3f
#define TIME_FOR_BOOSTER 15.0f
#define DAMAGE_RADIUS 100.0f
#define COUNT_LEVELS 5

using namespace cocos2d;
using namespace std;

enum class WeaponType  {
    RegularWeapon,
    NinjaStyle,
    MachineGun
};

class GameScene : public Scene {
private:
    
    SlashHandler *_slashHandler;
    MachineGuns *_machineGuns;
    
    WeaponType wType = WeaponType::RegularWeapon;
    
    vector<Bird*> birds;
    vector<Booster*> boosters;
    
    float cooldownTimer = 0.0f;
    float currentCooldown = DEFAULT_COOLDOWN_BIRDS;
    
    float boosterTime = 0.0f;
    
    int levelBarrier = DEFAULT_LEVEL_BARRIER;
    int levelDifficulty = 1;
    
    EventListenerTouchAllAtOnce *touchListener;
    GameUI *_gameUI;
    
    bool init();
    void initBackground();
    void initInterface();
    void initTouchListeners();
    void initSlashHandler();
    void initMachineGuns();
    
    BirdType getBirdType();
    void createBird();
    void createBooster();
    void removeBirdIfCuted(Point p);
    void removeBirdIfCaught(Point p);
    void removeBirdIfWounded(int idBird);
    void scoreBoosterIfWounded();
    bool launchBoosterIfTouched(Point p);
    
    void clearRemovedObjects();
    void scoreBird(int idBird);
    void launchBooster(int idBooster);
    void gameOver();
    void increaseDifficulty();
    void reduceCooldown();
    void makeBirdsFaster();
    void killBirds();
    void removeBirdsFromScreen();
    void reduceLife();
    
    //boosters methods
    void addLife();
    void slowBirds();
    
    
    void update(float dt);
    
public:
    
    CREATE_FUNC(GameScene);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
    void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
    void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
    
    void shakeDisplay();
    
};

#endif /* defined(__FallingBirdsGame__GameScene__) */
