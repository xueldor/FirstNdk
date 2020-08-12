拷贝nativeactivity_glue_window2，删除原来的直接操作像素的部分，添加OpenGL/ES演示

1、两个头文件
#include <EGL/egl.h>
#include <GLES2/gl2.h>

eglGetDisplay、eglInitialize、eglChooseConfig、eglGetConfigAttrib、eglCreateWindowSurface、eglCreateContext、eglMakeCurrent、eglSwapBuffers等egl开头的方法是EGL/egl.h里面的，
这个头文件用来将OpenGL ES绑定到android平台，上面列举的方法都是与安卓上下文紧密相关的。

GLES2/gl2.h才是核心的图形算法实现，glClearColor、glClear等方法出自于此。

2、android/asset_manager.h提供访问asset目录的支持

3、下载libpng的源码。 http://www.libpng.org/pub/png/libpng.html。
或者安卓aosp源码extra目录已经有了。
放到ndk\sources目录，将libpng/scripts/pnglibconf.h.prebuilt拷到外面，改名为pnglibconf.h。
在libpng目录编写Android.mk,可以参考aosp\extra\libpng下的Android.bp。然后在本应用的Android.mk中加进去：
LOCAL_STATIC_LIBRARIES := png
末尾：
$(call import-module,libpng)


4、在GraphicsManager::start中演示了在安卓NDK中使用OpenGL/ES的核心代码:
    mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(mDisplay,NULL,NULL)
    eglChooseConfig(mDisplay, DISPLAY_ATTRIBS, &config, 1,&numConfigs)
    eglGetConfigAttrib(mDisplay, config,EGL_NATIVE_VISUAL_ID, &format)
    eglCreateWindowSurface(mDisplay,config,mApplication->window,NULL)
    mContext = eglCreateContext(mDisplay, config, NULL,CONTEXT_ATTRIBS);
其实就是创建display、surface、context，然后设置到当前opengl环境中去：
    eglMakeCurrent(mDisplay,mSurface,mSurface,mContext)
这样opengl与android显示系统就连接起来了。然后就可以调用gl2.h里的方法：
    glViewport(0,0,mRenderWidth,mRenderHeight);
    glDisable(GL_DEPTH_TEST);
    //预置清除时使用的颜色
    glClearColor(clearColor,clearColor,clearColor,1.0f);
    //用上面设置的颜色清除缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
最后记得eglSwapBuffers(mDisplay,mSurface)将前面绘图的缓冲区推到前面

5、演示了用asset_manager加载asset目录下的文件，以及用libpng解析png图片。但是没有显示出来。以后完善