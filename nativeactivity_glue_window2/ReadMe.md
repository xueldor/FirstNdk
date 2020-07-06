在上一个例子nativeactivity_glue_window的基础上，让画面动起来。

void EventLoop::run()方法中，用ALooper_pollAll接收事件。将第一个参数传0，或者一个比较小的毫秒，这样while(true)里就会不断执行mActivityHandler.onStep()。
在onStep里面更新画面，界面不断刷新就形成动画。

