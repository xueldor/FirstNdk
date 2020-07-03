1、上一个例子nativeactivity_glue是一个空的activity，没有画面，呈现给用户的可能是一个黑色的区域。
本例子，我们将nativeactivity_glue拷贝一份，在此基础上增加绘图

2、
涉及头文件<android/native_window.h>,只需包含#include <android_native_app_glue.h>即可。
android_native_app_glue.h中封装了android_app结构体，包含ANativeWindow window对象

3、windowBuffer.bits指针让你直接访问window surface，通过该指针，给每个像素赋予ARGB值，来绘制色彩。

4、ANativeWindow_setBuffersGeometry(mApplication->window,0,0,WINDOW_FORMAT_RGBX_8888)
指定色彩格式是RGBX。RGBX表示有R、G、B、A四个通道，每个颜色值用32位存储，但是alpha通道的值始终是255.
比如0x000000FF代表红色，0x0000FF00绿色，0x00FF0000蓝色。前两位忽略。

5、ANativeWindow_lock(window, &windowBuffer, NULL) 、ANativeWindow_unlockAndPost(window)
在window上面绘图之前，必须先lock。结束后unlock。执行完ANativeWindow_unlockAndPost后，界面会立即刷新
通过lock得到windowBuffer对象，通过windowBuffer对象遍历window的每个像素。

6、windowBuffer.stride表示从一行跳跃到下一行的间隔距离。注意并不一定等于window宽度。
比如，在我的手机上，当我在ANativeWindow_setBuffersGeometry中指定width为500时，windowBuffer.width==500,但是windowBuffer.stride==512，
当指定width为512时，width==stride。当指定width为513时，stride==528。

所以，计算bits的下标时，一定要用stride来计算。

7、
如果ANativeWindow_lock后，没有用memset将windowBuffer.bits全部重置为0（黑色背景），画面每次刷新都会有些古怪，前一次的绘制内容若隐若现。
根据此现象，我推测每次ANativeWindow_lock后，获取的windowBuffer以及bits的地址虽然一样，但是系统底层的缓冲区至少有两个。不出意外应该是三个。
每次ANativeWindow_lock，依次遍历这三个缓冲区赋给上层应用。如果没有memset，实际是在上上上次的结果上继续绘制。
所以lock后，必须先将buffer的内存区域重置，再正常绘图。调用memset是一种简单暴力的方法。