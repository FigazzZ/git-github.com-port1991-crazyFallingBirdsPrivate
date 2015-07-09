//
//  ZFTimer.cpp
//  CheekyChips
//
//  Created by Pro on 4/3/15.
//
//

#include "ZFTimer.h"

ZFTimer::ZFTimer()
{
    this->checkTimer();
}

ZFTimer::~ZFTimer()
{
    
}

void ZFTimer::launchTimer(float timeWork, const function<void()>& func)
{
    if( func != NULL)
        _function = func;
    
    workingTime = timeWork;
    timerIsRunning = true;
    timerHasTask = true;
    
    timerMutex.lock();
    timerThread = std::thread(&ZFTimer::startTimer, this);
    timerThread.detach();
    timerMutex.unlock();
}

void ZFTimer::startTimer()
{
    while (timerIsRunning) {
        this->timerTick(0.1f);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void ZFTimer::timerTick(float deltaTime)
{
    workingTime -= deltaTime;
    if(workingTime <= 0.0f)
    {
        timerHasTask = false;
        this->callTheFunction();
    }
}

void ZFTimer::checkTimer()
{
    CCLOG("I'm here!");
}

void ZFTimer::callTheFunction()
{
    timerIsRunning = false;
    if(_function != NULL)
    {
        _function();
    }
}

void ZFTimer::stopTimer()
{
    timerHasTask = false;
    timerIsRunning = false;
    workingTime = 0.0f;
}

void ZFTimer::pauseTimer()
{
    CCLOG("Pause Timer");
    timerIsRunning = false;
}

void ZFTimer::resumeTimer()
{
    CCLOG("Resume Timer");
    timerIsRunning = true;
    
    timerMutex.lock();
    timerThread = std::thread(&ZFTimer::startTimer, this);
    timerThread.detach();
    timerMutex.unlock();
}