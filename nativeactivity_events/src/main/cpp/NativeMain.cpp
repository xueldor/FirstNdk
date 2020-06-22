//
// Created by xue on 2020/6/10.
//

#include <android/log.h>

#include <pthread.h>
#include <stdlib.h>
#include "NativeMain.h"

#define LOG_TAG "NATIVE_MAIN_CPP"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR ,LOG_TAG ,__VA_ARGS__)


static ALooper *threadLooper;
static int looper_id_input = 1;
static ANativeActivity *thisactivity;

//declare
int looperOnInputEvent(int fd, int events, void *data);

void onStart(ANativeActivity *activity) {
    LOGE("onStart");//从log看出，这些回调都是在主线程发生的
}

void onResume(ANativeActivity *activity) {
    LOGE("onResume");
}

void *onSaveInstanceState(ANativeActivity *activity, size_t *outSize) {
    LOGE("onSaveInstanceState");
}

void onPause(ANativeActivity *activity) {
    LOGE("onPause");
}

void onStop(ANativeActivity *activity) {
    LOGE("onStop");
}

void onDestroy(ANativeActivity *activity) {
    LOGE("onDestroy");
}

void onWindowFocusChanged(ANativeActivity *activity, int hasFocus) {
    LOGE("onWindowFocusChanged");
}

void onNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window) {
    LOGE("onNativeWindowCreated");
}

void onNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window) {
    LOGE("onNativeWindowDestroyed");
}

void onInputQueueCreated(ANativeActivity *activity, AInputQueue *queue) {
    AInputQueue_attachLooper(queue, threadLooper, looper_id_input, looperOnInputEvent, queue);
}

void onInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue) {
    AInputQueue_detachLooper(queue);
}

void onConfigurationChanged(ANativeActivity *activity) {
    LOGE("onConfigurationChanged");
}

void onLowMemory(ANativeActivity *activity) {
    LOGE("onLowMemory");
}


static void *threadRun(void *);

/**
 * 执行入口
 */
void ANativeActivity_onCreate(ANativeActivity *activity, void *savedState, size_t savedStateSize) {
    LOGE("onCreate");
    bindLifeCycle(activity);//绑定生命周期
    thisactivity = activity;
    threadLooper = ALooper_prepare(0);
}

void bindLifeCycle(ANativeActivity *activity) {
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onLowMemory = onLowMemory;
}

int OnInputEvent(AInputEvent *event) {
    float mx = AMotionEvent_getX(event, 0);
    float my = AMotionEvent_getY(event, 0);
    LOGE("Touch screen x=%f,y=%f", mx, my);

    switch (AInputEvent_getType(event)) {
        case AINPUT_EVENT_TYPE_MOTION: {
            switch (AMotionEvent_getAction(event)) {
                case AMOTION_EVENT_ACTION_DOWN: {
                    LOGE("Touch Scerrn Down");
                    break;
                }
                case AMOTION_EVENT_ACTION_UP: {
                    LOGE("Touch Scerrn UP");
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case AINPUT_EVENT_TYPE_KEY: {
            switch (AKeyEvent_getAction(event)) {
                case AKEY_EVENT_ACTION_DOWN: {
                    LOGE("key down");
                    switch (AKeyEvent_getKeyCode(event)) {
                        case AKEYCODE_BACK: {
                            LOGE("BACK down");
                            ANativeActivity_finish(thisactivity);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case AKEY_EVENT_ACTION_UP: {
                    LOGE("key up");
                    break;
                }
                default:
                    break;
            }
        }
        default:
            break;
    }
    return 0;
}

int looperOnInputEvent(int fd, int events, void *data) {
    AInputQueue *inputQueue = (AInputQueue *) data;
    AInputEvent *event;
    while (AInputQueue_getEvent(inputQueue, &event) >= 0) {
        if (AInputQueue_preDispatchEvent(inputQueue, event)) {
            continue;
        }
        AInputQueue_finishEvent(inputQueue, event, OnInputEvent(event));
    }

    return 1;
}