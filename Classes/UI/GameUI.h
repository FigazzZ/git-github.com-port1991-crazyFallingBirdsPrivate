//
//  GameUI.h
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#ifndef __FallingBirdsGame__GameUI__
#define __FallingBirdsGame__GameUI__

#include "cocos2d.h"
#include "ZFButton.h"
#include "ZFLabel.h"

using namespace cocos2d;
using namespace std;

class GameUI : public Layer {
    
    stack<Sprite*> stackLives;
    
    Sprite *whiteFade;
    Layer *menuLayer;
    ZFButton *btnPause;
    ZFLabel *labelScore;
    
    bool initUserInterface();
    void initDefaultInterface();
    void initLivesPanel();
    void initWhiteFade();
    void showPauseScreen();
    void clearPauseScreen();
    void showBombEffect();
    
    
    //button's functions
    void pauseGame();
    void goMainMenu();
    void restartGame();
    void continueGame();
    
    
public:
    
    static GameUI* createUserInterface();
    
    void addLife();
    void reduceLife();
    
    void updateLabelScore();
    void showGameOver();
    
    void showShrapnel(Point p);
    void showSparkles(Point p);
};

#endif /* defined(__FallingBirdsGame__GameUI__) */
