//
// Created by xue on 2020/6/10.
//

#include <android/log.h>

#include <pthread.h>
#include "NativeMain.h"

#define LOG_TAG "NATIVE_MAIN_CPP"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR ,LOG_TAG ,__VA_ARGS__)


static bool isLoop = false;
static pthread_t loopID;

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

}

void onNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window) {

}

void onNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window) {

}

void onInputQueueCreated(ANativeActivity *activity, AInputQueue *queue) {
    isLoop = true;
    activity->instance = (void *) queue;
    pthread_create(&loopID, NULL, looper, activity);
}

void onInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue) {
    isLoop = false;
}

void onConfigurationChanged(ANativeActivity *activity) {

}

void onLowMemory(ANativeActivity *activity) {

}

/**
 * 执行入口
 */
void ANativeActivity_onCreate(ANativeActivity *activity, void *savedState, size_t savedStateSize) {
    LOGE("onCreate");
    bindLifeCycle(activity);
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

void *looper(void *args) {
    LOGE("Event looper");
    //该方法是在onInputQueueCreated中创建子线程执行的。
    // 通过死循环从事件队列中取出事件。
    ANativeActivity *activity = (ANativeActivity *) args;
    AInputQueue *queue = (AInputQueue *) activity->instance;
    AInputEvent *event = NULL;
    while (isLoop) {//这里会出现死循环，而且没有暂停和阻塞，会占用很高CPU(单核100%)，是否可优化？
        if (!AInputQueue_hasEvents(queue)) {
            continue;
        }
        AInputQueue_getEvent(queue, &event);
        float mx = AMotionEvent_getX(event, 0);
        float my = AMotionEvent_getY(event, 0);
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
                                ANativeActivity_finish(activity);
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
        AInputQueue_finishEvent(queue, event, 1);
    }
    return args;
}