#include "EventLoop.h"
#include "Log.h"

EventLoop::EventLoop(android_app *pApplication, ActivityHandler& pActivityHandler):
            mApplication(pApplication),mEnabled(false), mQuit(false),
            mActivityHandler(pActivityHandler){
    mApplication->userData = this;//可以是任何对象，根据你的需要
    mApplication->onAppCmd = callback_appEvent;//指向生命周期事件的回调函数
    mApplication->onInputEvent = callback_inputEvent;//指向输入、按键事件的回调函数

}

void EventLoop::run() {
    int32_t events;
    android_poll_source* source;

    Log::info("Starting event loop");
    while (true){
        //当timeout==-1时， ALooper_pollAll()保持阻塞，直到有一个event。处理完event通过while继续阻塞
        //当timeout==0时， ALooper_pollAll()立即返回，如果没有可以poll的事件，返回值为负数，执行opStep
        while(ALooper_pollAll(mEnabled ? 0 : -1,NULL,&events,(void**)&source) >= 0){
            if(source != NULL){
                if(source == &mApplication->inputPollSource){
                    Log::info("Processing an input event");
                    source ->process(mApplication,source);
                }else if(source == &mApplication->cmdPollSource){
                    Log::info("Processing an cmd event");
                    source ->process(mApplication,source);
                }
            }
            if(mApplication->destroyRequested){
                Log::info("Exiting event loop");
                return;
            }
        }

        //如果ALooper_pollAll返回负数，表示阻塞被唤醒、超时、出错、没有消息等。这时会走到这里。
        Log::warn("mEnabled=%d,mQuit=%d",mEnabled,mQuit);
        if((mEnabled && !mQuit)){
            if(mActivityHandler.onStep() != STATUS_OK){
                mQuit = true;
                Log::info("ANativeActivity_finish");
                ANativeActivity_finish(mApplication->activity);
            }
        }
    }
}

void EventLoop::activate() {
    // Enables activity only if a window is available.
    if ((!mEnabled) && (mApplication->window != NULL)) {
        mQuit = false; mEnabled = true;
        if (mActivityHandler.onActivate() != STATUS_OK) {
            goto ERROR;
        }
    }
    return;
    ERROR:
    mQuit = true;
    deactivate();
    ANativeActivity_finish(mApplication->activity);
}

void EventLoop::deactivate() {
    if (mEnabled) {
        mActivityHandler.onDeactivate();
        mEnabled = false;
    }
}

void EventLoop::callback_appEvent(android_app* pApplication,
                                  int32_t pCommand) {
    EventLoop& eventLoop = *(EventLoop*) pApplication->userData;
    eventLoop.processAppEvent(pCommand);
}
int32_t EventLoop::callback_inputEvent(android_app* pApplication,AInputEvent* event) {
    Log::info("callback_inputEvent,pCommand=%d",AInputEvent_getType(event));
    return 0;
}

void EventLoop::processAppEvent(int32_t pCommand) {
    switch (pCommand) {
        case APP_CMD_CONFIG_CHANGED:
            mActivityHandler.onConfigurationChanged();
            break;
        case APP_CMD_INIT_WINDOW:
            mActivityHandler.onCreateWindow();
            break;
        case APP_CMD_DESTROY:
            mActivityHandler.onDestroy();
            break;
        case APP_CMD_GAINED_FOCUS:
            activate();
            mActivityHandler.onGainFocus();
            break;
        case APP_CMD_LOST_FOCUS:
            mActivityHandler.onLostFocus();
            deactivate();
            break;
        case APP_CMD_LOW_MEMORY:
            mActivityHandler.onLowMemory();
            break;
        case APP_CMD_PAUSE:
            mActivityHandler.onPause();
            deactivate();
            break;
        case APP_CMD_RESUME:
            mActivityHandler.onResume();
            break;
        case APP_CMD_SAVE_STATE:
            mActivityHandler.onSaveInstanceState(
                    &mApplication->savedState, &mApplication->savedStateSize);
            break;
        case APP_CMD_START:
            mActivityHandler.onStart();
            break;
        case APP_CMD_STOP:
            mActivityHandler.onStop();
            break;
        case APP_CMD_TERM_WINDOW:
            mActivityHandler.onDestroyWindow();
            deactivate();
            break;
        default:
            Log::info("processAppEvent,pCommand=%d",pCommand);
            break;
    }
}