
#ifndef FIRSTNDK_ACTIVITYHANDLER_H
#define FIRSTNDK_ACTIVITYHANDLER_H

#include "Types.h"

//接口
class ActivityHandler {
public:
    virtual ~ActivityHandler(){};

    virtual status onActivate() = 0;
    virtual void onDeactivate() = 0;
    virtual status onStep() = 0;

    virtual void onStart() {};
    virtual void onResume() {};
    virtual void onPause() {};
    virtual void onStop() {};
    virtual void onDestroy() {};

    virtual void onSaveInstanceState(void** pData, size_t* pSize) {};
    virtual void onConfigurationChanged() {};
    virtual void onLowMemory() {};

    virtual void onCreateWindow() {};
    virtual void onDestroyWindow() {};
    virtual void onGainFocus() {};
    virtual void onLostFocus() {};
};
#endif //FIRSTNDK_ACTIVITYHANDLER_H
