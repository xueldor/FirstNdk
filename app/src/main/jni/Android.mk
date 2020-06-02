LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := JniLib
LOCAL_SRC_FILES := Jni2Lib.cpp JniLib.cpp Jni3Lib.cpp Jni4Lib.cpp Jni5Lib.cpp

#使用__android_log_print需要添加
LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -llog

#NDK r5 版本开始,NDK开始支持C++异常控制,需要手动打开
LOCAL_CPP_FEATURES += exceptions

#对一些老版本的安卓需要放开下行，否则无法加载so
libsysv-hash-table-library_ldflags := Wl,-hash-style=sysv

include $(BUILD_SHARED_LIBRARY)