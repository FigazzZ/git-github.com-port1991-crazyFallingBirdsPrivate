//
//  ZorrendorLabel.cpp
//  HelloCpp
//
//  Created by Andriy Prosekov on 10/22/14.
//
//

#include "ZFLabel.h"

ZFLabel* ZFLabel::createWithTTF(const std::string &text, const std::string &fontFile, float fontSize, int typeLabel)
{
    auto ret = new ZFLabel();
    ret->init(text, fontFile, fontSize, typeLabel);
    ret->autorelease();
    return ret;
}

bool ZFLabel::init(const std::string &text, const std::string &fontFile, float fontSize, int typeLabel)
{
    if (!Node::init())
    {
        return false;
    }
    
    switch (typeLabel) {
        case labelRegular:
        {
            firstLabel = Label::createWithTTF(text, fontFile, fontSize);
            firstLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            firstLabel->setPosition(0, 0);
            this->addChild(firstLabel);
            
            secondLabel = Label::createWithTTF(text, fontFile, fontSize);
            secondLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            secondLabel->setPosition(0, 0);
            this->addChild(secondLabel);
        }
            break;
        case labelShadow:
        {
            
            firstLabel = Label::createWithTTF(text, fontFile, fontSize);
            firstLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            firstLabel->setPosition(0, 0);
            firstLabel->enableShadow();
            this->addChild(firstLabel);
            
            secondLabel = Label::createWithTTF(text, fontFile, fontSize);
            secondLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            secondLabel->setPosition(0, 0);
            this->addChild(secondLabel);
        }
            break;
        case labelBorder:
        {
            firstLabel = Label::createWithTTF(text, fontFile, fontSize);
            firstLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            firstLabel->setPosition(0, 0);
            this->addChild(firstLabel);
           // firstLabel->enableOutline(Color4B(255, 255, 255, 255));
            
            secondLabel = Label::createWithTTF(text, fontFile, fontSize + 5); //COME BACK LATER TO FIX THIS BUGS
            secondLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            secondLabel->setPosition(0, 0);
            //secondLabel->setScale(1.04f);
            secondLabel->setColor(Color3B::BLACK);
            this->addChild(secondLabel);
        }
            break;
        default:
            break;
    }
    
    return true;
}

void ZFLabel::changeString(const std::string &newString)
{
    if (strcmp(firstLabel->getString().c_str(), newString.c_str()) == 0)
    {
        return;
    }
    
    firstLabel->setScale(1);
    secondLabel->setScale(0);
    
    secondLabel->setString(newString);
    firstLabel->runAction(ScaleTo::create(0.2, 0));
    secondLabel->runAction(ScaleTo::create(0.2, 1));
    
    Sequence *seq;
    
    seq = Sequence::create(DelayTime::create(0.2),
                           CallFunc::create(std::bind(&ZFLabel::applyChanges, this)),
                           NULL);
    
    this->runAction(seq);
}

void ZFLabel::applyChanges()
{
    firstLabel->setString(secondLabel->getString());
}

void ZFLabel::setString(const std::string &newString)
{
    firstLabel->setString(newString);
    secondLabel->setString(newString);
}

void ZFLabel::setColor(cocos2d::Color3B color)
{
    firstLabel->setColor(color);
    secondLabel->setColor(color);
}

void ZFLabel::setLineSize(int value)
{
    firstLabel->setMaxLineWidth(value);
    secondLabel->setMaxLineWidth(value);
}

void ZFLabel::setFont(std::string fontName)
{
    firstLabel->setSystemFontName(fontName);
    secondLabel->setSystemFontName(fontName);
}

void ZFLabel::setFontSize(int value)
{
    TTFConfig configFont;
    configFont.fontFilePath = "PENULLI.TTF";
    configFont.fontSize = value;
    firstLabel->setTTFConfig(configFont);
    secondLabel->setTTFConfig(configFont);
}

void ZFLabel::deleteLabel()
{
    this->removeFromParentAndCleanup(true);
}