//
//  TutorialScreen.h
//  FallingBirdsGame
//
//  Created by user on 29/06/15.
//
//

#ifndef __FallingBirdsGame__TutorialScreen__
#define __FallingBirdsGame__TutorialScreen__

#include "cocos2d.h"

using namespace cocos2d;

class TutorialScreen : public Layer {
private:
    
    Layer *interfaceLayer;
    Menu *btnsMenu;
    
    bool initTutorialLayer();
    void initBackground();
    void initButtonBack();
    
    void initExplanation();
    void explanationBooster0();
    void explanationBooster1();
    void explanationBooster2();
    
    void hideTurorialLayer();
    void removeInterface();
    
    //button functions
    void backPressed();
    
public:
    
    static TutorialScreen* createTutorialLayer();
};

#endif /* defined(__FallingBirdsGame__TutorialScreen__) */
