//
//  GameScene.cpp
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#include "GameScene.h"
#include "Constants.h"
#include "Bullet.h"

bool GameScene::init()
{
    if( !Scene::init() )
        return false;
    
    wType = WeaponType::RegularWeapon;
    this->initTouchListeners();
    this->initBackground();
    this->initInterface();
    this->initSlashHandler();
    
    //just for test
    //this->initMachineGuns();
    //_machineGuns->showMachineGuns();
    
    this->schedule(schedule_selector(GameScene::update));
    
    if(singleton->isSound())
        singleton->changeBackgroundMusicVolume(0.2f);
    
    return true;
}

void GameScene::initBackground()
{
    Sprite *sprBackground = Sprite::create("gameBack.png");
    sprBackground->setPosition(winSize.width*0.5, winSize.height*0.5);
    this->addChild(sprBackground);
}

void GameScene::initInterface()
{
    _gameUI = GameUI::createUserInterface();
    _gameUI->setPosition(Point::ZERO);
    this->addChild(_gameUI, 3);
}

void GameScene::initTouchListeners()
{
    this->getEventDispatcher()->removeEventListenersForTarget(this);
    
    touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::initSlashHandler()
{
    _slashHandler = SlashHandler::createSlashHandler();
    _slashHandler->setPosition(Point::ZERO);
    this->addChild(_slashHandler, 2);
}

void GameScene::initMachineGuns()
{
    _machineGuns = MachineGuns::createMachineGuns();
    _machineGuns->setPosition(Point::ZERO);
    this->addChild(_machineGuns, 2);
}

void GameScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event)
{
    if(singleton->isPaused() || singleton->isGameOver())
        return;
    
    Touch *touch = touches.at(0);
    Point p = touch->getLocation();
    
    switch (wType) {
        case WeaponType::RegularWeapon:
        {
            _gameUI->showShrapnel(p);
            if(this->launchBoosterIfTouched(p))
                break;
            this->removeBirdIfCaught(p);
            this->clearRemovedObjects();
        }
            break;
        case WeaponType::NinjaStyle:
        {
            _slashHandler->resetBladeCut();
            this->launchBoosterIfTouched(p);
        }
            break;
        case WeaponType::MachineGun:
        {
            _machineGuns->directGuns(p);
            _machineGuns->startShooting();
        }
            break;
        default:
            break;
    }
}

void GameScene::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event)
{
    if(singleton->isPaused() || singleton->isGameOver())
        return;
    
    Touch *touch = touches.at(0);
    Point p = touch->getLocation();
    
    switch (wType) {
        case WeaponType::NinjaStyle:
        {
            _slashHandler->addBladeCut(p);
            this->removeBirdIfCuted(p);
            this->launchBoosterIfTouched(p);
        }
            break;
        case WeaponType::MachineGun:
        {
            _machineGuns->directGuns(p);
        }
            break;
        default:
            break;
    }
    
    this->clearRemovedObjects();
}

void GameScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event)
{
    if(singleton->isPaused() || singleton->isGameOver())
        return;
    
    if(wType == WeaponType::MachineGun)
    {
        _machineGuns->endShooting();
    }
    
}

void GameScene::removeBirdIfCuted(Point p)
{
    for (int i = 0; i < birds.size(); i++) {
        if (birds[i]->getRectObject().containsPoint(p)) {
            this->scoreBird(i);
        }
    }
}

void GameScene::removeBirdIfCaught(Point p)
{
    int countSteps = 5;
    bool missed = true;
    for (int i = 0; i < birds.size(); i++) {
        Vec2 direction = Vec2(birds[i]->getPositionObject() - p);
        direction.normalize();
        for (int j = 0; j <= countSteps; j++) {
            Point currentPoint = Point(p.x + (j * (DAMAGE_RADIUS/countSteps) * direction.x),
                                       p.y + (j * (DAMAGE_RADIUS/countSteps) * direction.y));
            
            if(birds[i]->getRectObject().containsPoint(currentPoint))
            {
                missed = false;
                this->scoreBird(i);     //because array is less after every move, some birds just misses
                j = countSteps;
            }
        }
        //INTERSECTS CIRCLE!!!
    }
    
    if(missed)
    {
        singleton->playSound(SoundType::MissedShot);
    }
    else
    {
        singleton->playSound(SoundType::HitTheBird);
    }
}

void GameScene::removeBirdIfWounded(int idBird)
{
    for (int i = 0; i < _machineGuns->getBullets().size(); i++) {
        Bullet *b = (Bullet*)_machineGuns->getBullets().at(i);
        if(birds[idBird]->getRectObject().containsPoint(b->getBulletPosition()))
        {
            _gameUI->showSparkles(b->getBulletPosition());
            b->removeBullet();
            this->scoreBird(idBird);
            return;
        }
    }
    
    this->clearRemovedObjects();
}

void GameScene::scoreBoosterIfWounded()
{
    for (int i = 0; i <_machineGuns->getBullets().size(); i++) {
        Bullet *b = (Bullet*)_machineGuns->getBullets().at(i);
        
        for (int j = 0; j < boosters.size(); j++) {
            if(boosters[j]->getRectObject().containsPoint(b->getBulletPosition()))
            {
                b->removeBullet();
                this->launchBooster(j);
                return;
            }
        }
    }
}

bool GameScene::launchBoosterIfTouched(Point p)
{
    for (int i = 0; i < boosters.size(); i++) {
        if (boosters[i]->getRectObject().containsPoint(p)) {
            this->launchBooster(i);
            return true;
        }
    }
    
    return false;
}

void GameScene::clearRemovedObjects()
{
    int counter = 0;
    while (counter != birds.size()) {
        
        if(birds[counter]->isRemoved())
        {
            birds[counter]->removeObject();
            birds.erase(birds.begin() + counter);
            counter--;
        }
        
        counter++;
    }
}

void GameScene::update(float dt)
{
    if (singleton->isPaused() || singleton->isGameOver()) {
        return;
    }
    
    cooldownTimer += dt;
    boosterTime += dt;
    
    if(cooldownTimer >= currentCooldown)
    {
        this->createBird();
        cooldownTimer = 0.0f;
    }
    
    if(boosterTime >= TIME_FOR_BOOSTER)
    {
        this->createBooster();
        boosterTime = 0.0f;
    }
    
    for (int i = 0; i < birds.size(); i++) {
        
        bool alreadyDeleted = false;
        
        if (birds[i]->passed()) {
            alreadyDeleted = true;
            birds[i]->deleteObject();
            birds.erase(birds.begin() + i);
            
            this->reduceLife();
        }
        
        if(wType == WeaponType::MachineGun && !alreadyDeleted)
        {
            this->removeBirdIfWounded(i);
        }
    }
    
    
    if (wType == WeaponType::MachineGun) {
        this->scoreBoosterIfWounded();
    }
}

BirdType GameScene::getBirdType()
{
    float firstPossibility = arc4random()%100 / 100.0f;
    float regularBirdPossibility = 0.9f - levelDifficulty/10.0f;
    if(regularBirdPossibility < 0.4f)
        regularBirdPossibility = 0.4f;
    
    
    if (firstPossibility <= regularBirdPossibility) {
        return BirdType::REGULAR_BIRD;
    }
    else
    {
        float secondPossibility = arc4random()%100 / 100.0f;
        
        if (secondPossibility < 0.5f) {
            return BirdType::SPEEDY_BIRD;
        }   else    {
            return BirdType::BIG_BIRD;
        }
    }
}

void GameScene::createBird()
{
    Bird *_bird = Bird::createBird(arc4random()%(int)(winSize.width*0.85) + winSize.width*0.1, this->getBirdType());
    _bird->setPosition(Point::ZERO);
    this->addChild(_bird);
    birds.push_back(_bird);
}

void GameScene::createBooster()
{
    BoosterType bType;
    
    float randomBoost = arc4random()%100 / 100.0f;
    if (randomBoost < 0.15f) {
        bType = BoosterType::Life;
    }
    else if (randomBoost < 0.6f)
    {
        bType = BoosterType::SlowBirds;
    }
    else
    {
        bType = BoosterType::KillBirds;
    }
    
    if(bType == BoosterType::Life && singleton->isLivesFull())
    {
        randomBoost = arc4random()%100 / 100.0f;
        if (randomBoost < 0.5f) {
            bType = BoosterType::SlowBirds;
        }   else    {
            bType = BoosterType::KillBirds;
        }
    }
    
    Booster* _booster = Booster::createBooster(BoosterType::SlowBirds, arc4random()%(int)(winSize.width*0.85) + winSize.width*0.1);
    _booster->setPosition(Point::ZERO);
    this->addChild(_booster);
    boosters.push_back(_booster);
}

void GameScene::scoreBird(int idBird)
{
    birds[idBird]->setRemoved();
    singleton->collectBird();
    _gameUI->updateLabelScore();
    
    if(singleton->getGameScore() % levelBarrier == 0 && levelDifficulty != COUNT_LEVELS) {
        this->increaseDifficulty();
    }
}

void GameScene::launchBooster(int idBooster)
{
    switch (boosters[idBooster]->getBoosterType()) {
        case BoosterType::Life:
        {
            if(!singleton->isLivesFull())   {
                this->addLife();
                singleton->playSound(SoundType::PickLife);
            }
        }
            break;
        case BoosterType::SlowBirds:
        {
            this->slowBirds();
            singleton->playSound(SoundType::SlowDown);
        }
            break;
        case BoosterType::KillBirds:
        {
            this->killBirds();
            singleton->playSound(SoundType::Boom);
        }
            break;
        default:
            break;
    }
    
    boosters[idBooster]->removeObject();
    boosters.erase(boosters.begin() + idBooster);
}

void GameScene::addLife()
{
    singleton->addLife();
    _gameUI->addLife();
}

void GameScene::slowBirds()
{
    singleton->slowBirdSpeed(&birds);
}

void GameScene::reduceLife()
{
    singleton->reduceLife();
    _gameUI->reduceLife();
    
    if(singleton->getLives() == 0)
        this->gameOver();
}

void GameScene::gameOver()
{
    if(wType == WeaponType::MachineGun)
    {
        _machineGuns->endShooting();
    }
    
    if(!singleton->isAdsRemoved())
        singleton->showAds();
    
    singleton->setGameOver();
    singleton->saveCoins();
    this->unschedule(schedule_selector(GameScene::update));
    _gameUI->showGameOver();
    this->removeBirdsFromScreen();
    singleton->postCurrentScore();
}

void GameScene::increaseDifficulty()
{
    this->reduceCooldown();
    levelBarrier *= 2;
    levelDifficulty++;
    this->makeBirdsFaster();
}

void GameScene::reduceCooldown()
{
    currentCooldown -= currentCooldown*0.3f;
}

void GameScene::makeBirdsFaster()
{
    singleton->increaseBirdSpeed();
    
    for (int i = 0; i < birds.size(); i++) {
        birds[i]->updateSpeed();
    }
}

void GameScene::killBirds()
{
    for (int i = 0; i < birds.size(); i++) {
        birds[i]->removeObject();
        singleton->collectBird();
    }
    
    _gameUI->updateLabelScore();
    birds.clear();
}

void GameScene::removeBirdsFromScreen()
{
    for (int i = 0; i < birds.size(); i++) {
        birds[i]->removeObject();
    }
    
    birds.clear();
}

void GameScene::shakeDisplay()
{
    this->runAction(Sequence::create(MoveTo::create(0.04f, Point(this->getPositionX() + 4.0f, this->getPositionY() - 2.0f)),
                                     MoveTo::create(0.04f, Point(this->getPositionX() - 3.0f, this->getPositionY() + 1.0f)),
                                     MoveTo::create(0.02f, this->getPosition()),
                                     NULL));
}