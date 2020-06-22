//
// Created by xue on 2020/6/10.
//

#ifndef NATIVEEVENTTEST_NATIVEMAIN_H
#define NATIVEEVENTTEST_NATIVEMAIN_H

//这个例子我们不使用<android_native_app_glue.h>，直接使用native_activity.h实现
#include <android/native_activity.h>

/*
 * 定义绑定声明周期函数
 */
void bindLifeCycle(ANativeActivity *activity);

/*
 * 定义NativeActivity的入口函数
 */
void ANativeActivity_onCreate(ANativeActivity *activity, void *savedState, size_t savedStateSize);

/*
 * 处理事件队列的函数
 */
void *looper(void *args);

/**
 * 定义onStart方法,对应Java中的onStart
 */
void onStart(ANativeActivity *activity);

/**
 * 定义onResume方法,对应Java中的onResume
 */
void onResume(ANativeActivity *activity);

/**
 * 定义储存静态对象状态方法
 */
void *onSaveInstanceState(ANativeActivity *activity, size_t *outSize);

/**
 * 定义onPause方法,对应Java中的onPause
 */
void onPause(ANativeActivity *activity);

/**
 * 定义onStop方法,对应Java中的onStop
 */
void onStop(ANativeActivity *activity);

/**
 * 定义onDestory方法,对应Java中的onDestroy
 */
void onDestroy(ANativeActivity *activity);

/**
 * 定义窗口焦点改变方法
 */
void onWindowFocusChanged(ANativeActivity *activity, int hasFocus);

/**
 * 定义Native窗口创建方法
 */
void onNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window);

/**
 * 定义Native窗口销毁方法
 */
void onNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window);

/**
 * 定义输入队列创建方法
 */
void onInputQueueCreated(ANativeActivity *activity, AInputQueue *queue);

/**
 * 定义输入队列销毁方法
 */
void onInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue);

/**
 * 定义配置改变方法
 */
void onConfigurationChanged(ANativeActivity *activity);

/**
 * 定义低内存方法
 */
void onLowMemory(ANativeActivity *activity);

#endif //NATIVEEVENTTEST_NATIVEMAIN_H
