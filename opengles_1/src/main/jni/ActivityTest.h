//
// Created by xue on 2020/6/22.
//

#ifndef FIRSTNDK_ACTIVITYTEST_H
#define FIRSTNDK_ACTIVITYTEST_H

#include "ActivityHandler.h"
#include "EventLoop.h"
#include "Types.h"
#include "GraphicsManager.h"
#include "Ship.h"
#include "Square.h"
#include "PhysicsManager.h"
#include "TimeManager.h"
#include "Resource.h"

//实现接口ActivityHandler
class ActivityTest: public ActivityHandler{
public:
    ActivityTest(android_app* pApplication);
    void run();

protected:
    status onActivate();
    void onDeactivate();
    status onStep();

    void onStart();
    void onResume();
    void onPause();
    void onStop();
    void onDestroy();

    void onSaveInstanceState(void** pData, size_t* pSize);
    void onConfigurationChanged();
    void onLowMemory();

    void onCreateWindow();
    void onDestroyWindow();
    void onGainFocus();
    void onLostFocus();

private:
    EventLoop mEventLoop;
    Resource mAsteroidTexture;
    Resource mShipTexture;

    GraphicsManager mGraphicsManager;
    TimeManager     mTimeManager;
    PhysicsManager  mPhysicsManager;
};

#endif //FIRSTNDK_ACTIVITYTEST_H
