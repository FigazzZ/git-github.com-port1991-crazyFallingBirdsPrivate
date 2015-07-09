//
//  SlashHandler.cpp
//  FallingBirdsGame
//
//  Created by user on 02/07/15.
//
//

#include "SlashHandler.h"
#include "Constants.h"

#define BLADE_CUT_TAG 5

SlashHandler* SlashHandler::createSlashHandler()
{
    SlashHandler *sh = new SlashHandler;
    
    if(sh->initSlashHandler())
    {
        sh->autorelease();
        return sh;
    }   else    {
        delete sh;
        return NULL;
    }
}

bool SlashHandler::initSlashHandler()
{
    if( !Layer::init() )    {
        return false;
    }
    
    return true;
}

void SlashHandler::initShader()
{
    GLProgram *p = new GLProgram();
    p->initWithFilenames("Base.vsh", "SlashHandler.fsh");
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->autorelease();
    p->link();
    p->updateUniforms();
    
    slashSprite->setGLProgram(p);
    
}

void SlashHandler::resetBladeCut()
{
    this->removeChildByTag(BLADE_CUT_TAG, true);
    MotionStreak *streak = MotionStreak::create(0.3f, 10, 60, Color3B::RED, "slash.png");
    this->addChild(streak, 5, BLADE_CUT_TAG);
}

void SlashHandler::addBladeCut(Point point)
{
    MotionStreak* streak = (MotionStreak*)this->getChildByTag(BLADE_CUT_TAG);
    streak->setPosition(point);
}