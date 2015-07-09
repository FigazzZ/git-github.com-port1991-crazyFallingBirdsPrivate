//
//  MainMenu.h
//  FallingBirdsGame
//
//  Created by user on 22/06/15.
//
//

#ifndef __FallingBirdsGame__MainMenu__
#define __FallingBirdsGame__MainMenu__

#include "cocos2d.h"
#include "TutorialScreen.h"
#include "ZFButton.h"

using namespace cocos2d;

class MainMenu : public Scene {
private:
    
    Menu *btnsMenu;
    Layer *interfaceLayer;
    Layer *tutorialLayer;
    TutorialScreen *tScreen;
    ZFButton *btnSound;
    
    bool init();
    void initBackground();
    void initButtons();
    void initTutorialScreen();
    void showTutorialScreen();
    void removeInterface();
    
    //button functions
    void playPressed();
    void gameCenterPressed();
    void tutorialPressed();
    void storePressed();
    void removeAdsPressed();
    void restorePurchasesPressed();
    void soundPressed();
    
public:
    CREATE_FUNC(MainMenu);
};

#endif /* defined(__FallingBirdsGame__MainMenu__) */
