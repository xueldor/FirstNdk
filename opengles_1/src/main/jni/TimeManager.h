#ifndef FIRSTNDK_TIMEMANAGER_H
#define FIRSTNDK_TIMEMANAGER_H

#include "Types.h"
#include <ctime>

class TimeManager {
public:
    TimeManager();
    void reset();
    void update();
    double now();
    float elapsed() { return mElapsed; };
    float elapsedTotal() { return mElapsedTotal; };


private:
    double mFirstTime;
    double mLastTime;
    float mElapsed;
    float mElapsedTotal;
};


#endif //FIRSTNDK_TIMEMANAGER_H
