#include "TimeManager.h"
#include "Log.h"

#include <cstdlib>

TimeManager::TimeManager() :
        mFirstTime(0.0f),mLastTime(0.0f),mElapsed(0.0f),mElapsedTotal(0.0f){
    srand(time(NULL));
}

void TimeManager::reset() {
    Log::info("Resetting TimeManager.");
    mElapsed = 0.0f;
    mFirstTime = now();
    mLastTime = mFirstTime;
}

void TimeManager::update() {
    double currentTime = now();//用double防止精度丢失
    mElapsed = (currentTime - mLastTime);
    mElapsedTotal = (currentTime - mFirstTime);
    mLastTime = currentTime;
}

double TimeManager::now() {
    timespec timeVal;
    clock_gettime(CLOCK_MONOTONIC,&timeVal);//CLOCK_MONOTONIC表示单调递增时间。系统重启到现在的时间。不受修改系统时间或穿越时区的影响。
    return timeVal.tv_sec + (timeVal.tv_nsec * 1.0e-9);
}