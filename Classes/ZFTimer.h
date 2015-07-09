//
//  ZFTimer.h
//  CheekyChips
//
//  Created by Pro on 4/3/15.
//
//

#ifndef __CheekyChips__ZFTimer__
#define __CheekyChips__ZFTimer__

#include "cocos2d.h"

using namespace std;

class ZFTimer
{
private:
    
    bool timerHasTask = false;
    bool timerIsRunning = false;
    float workingTime = 0.0f;
    std::thread timerThread;
    mutex timerMutex;
    function<void()> _function;
    
    void startTimer();
    void timerTick(float deltaTime);
    void checkTimer();
    void callTheFunction();
    
public:
    
    ZFTimer();
    ~ZFTimer();
    
    void launchTimer(float timeWork, const function<void()>& func = NULL);
    void pauseTimer();
    void resumeTimer();
    void stopTimer();
    bool ifTimerHasTask() const {   return timerHasTask;    }
};

#endif /* defined(__CheekyChips__ZFTimer__) */
