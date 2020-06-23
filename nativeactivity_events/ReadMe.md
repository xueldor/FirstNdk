在nativeactivity_lifecycle中，已经演示了NativeActivity的创建、生命周期。但是其中处理点击事件和按键事件是通过一个轮询主动从inputqueue中查询得到的。
我们改为用looper通知事件，更加合理。

1、在ANativeActivity_onCreate中用ALooper_prepare(0)得到指向主线程上的looper的指针
2、在onInputQueueCreated函数中，用AInputQueue_attachLooper将事件队列与looper绑定起来，指定事件回调函数。
3、在回调函数中用AInputQueue_getEvent得到事件对象。
4、事件处理完成后调用AInputQueue_finishEvent告诉系统，事件已经消费。

事件回调函数的片段：
while (AInputQueue_getEvent(inputQueue, &event) >= 0) {
        if (AInputQueue_preDispatchEvent(inputQueue, event)) {
            continue;
        }
        AInputQueue_finishEvent(inputQueue, event, OnInputEvent(event));
    }
官方提供的android_native_app_glue.c封装了一些细节，可以找到process_input函数，函数实现与上面的片段相类似。
后面的例子用glue实现，无需再写这种代码。