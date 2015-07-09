//
//  SlashHandler.h
//  FallingBirdsGame
//
//  Created by user on 02/07/15.
//
//

#ifndef __FallingBirdsGame__SlashHandler__
#define __FallingBirdsGame__SlashHandler__

#include "cocos2d.h"

using namespace cocos2d;

class SlashHandler : public Layer {
private:
    
    Sprite *slashSprite;
    
    bool initSlashHandler();
    void initShader();
    
public:
    
    static SlashHandler* createSlashHandler();
    
    void resetBladeCut();
    void addBladeCut(Point point);
};

#endif /* defined(__FallingBirdsGame__SlashHandler__) */
