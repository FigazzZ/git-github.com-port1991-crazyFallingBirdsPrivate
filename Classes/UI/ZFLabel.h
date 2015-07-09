//
//  ZorrendorLabel.h
//  HelloCpp
//
//  Created by Andriy Prosekov on 10/22/14.
//
//

#ifndef __HelloCpp__ZFLabel__
#define __HelloCpp__ZFLabel__

#include "cocos2d.h"
using namespace cocos2d;

typedef enum
{
    labelRegular,
    labelShadow,
    labelBorder,
}labelTypes;

class ZFLabel : public Node
{
    Label *firstLabel, *secondLabel;
    
    bool init(const std::string& text, const std::string& fontFile, float fontSize, int typeLabel);
    
    void applyChanges();
    
public:
    static ZFLabel* createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, int typeLabel);
    void setString(const std::string& newString);
    void changeString(const std::string& newString);
    void setColor(Color3B color);
    void deleteLabel();
    void setLineSize(int value);
    void setFont(std::string fontName);
    void setFontSize(int value);
    Rect getLabelRect() {   return firstLabel->getBoundingBox();    }
    
    
};

#endif /* defined(__HelloCpp__ZorrendorLabel__) */
