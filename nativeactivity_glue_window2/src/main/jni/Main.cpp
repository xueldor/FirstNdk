//
// Created by xue on 2020/6/9.
//

#include "ActivityTest.h"
#include "EventLoop.h"
#include "Log.h"

//真正的应用入口是ANativeActivity_onCreate()，不过android_native_app_glue.c帮我们封装了。参考前面的demo
//android_main运行在独立的native线程上，在它里面实现event loop，与UI线程上的NativeActivity分离开，避免因为处理事件导致NativeActivity阻塞
void android_main(android_app* pApplication) {
    ActivityTest(pApplication).run();//通过Log可以看到这不是主线程
}