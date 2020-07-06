#ifndef FIRSTNDK_EVENTLOOP_H
#define FIRSTNDK_EVENTLOOP_H

#include "ActivityHandler.h"
#include <android_native_app_glue.h>

class EventLoop{
public:
    EventLoop(android_app* pApplication, ActivityHandler& pActivityHandler);
    void run();

private:
    void activate();
    void deactivate();
    void processAppEvent(int32_t pCommand);
    static void callback_appEvent(android_app* pApplication,
                                  int32_t pCommand);
    static int32_t callback_inputEvent(android_app* pApplication,AInputEvent* event);
private:
    android_app * mApplication;
    bool mEnabled;
    bool mQuit;
    ActivityHandler& mActivityHandler;
};

#endif //FIRSTNDK_EVENTLOOP_H
