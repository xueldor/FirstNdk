app:演示基本的jni语法、使用

testalooper:演示用管道和ALooper实现线程间消息的传递和触发

livecamera: 演示<android/bitmap.h>操作bitmap

nativeactivity_lifecycle:演示用纯C++的方式新建activity，处理生命周期回调。并用一种不完美的方法实现触摸事件的处理

nativeactivity_events:相比于nativeactivity_lifecycle，用更合理的方法实现NativeActivity监听触摸事件和按键事件

nativeactivity_glue:用android_native_app_glue.c实现前面两个例子的功能

nativeactivity_glue_window:在nativeactivity_glue的基础上，增加获取window surface，并在上面绘制一个矩形(直接对像素赋值)

nativeactivity_glue_window2:在nativeactivity_glue_window的基础上，增加动画效果。

testexecutable: 生成可执行程序，push到手机执行。
