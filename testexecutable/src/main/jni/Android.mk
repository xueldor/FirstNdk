LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := testexe
LOCAL_SRC_FILES := TestPrint.cpp

#使用__android_log_print需要添加
LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -llog

#NDK r5 版本开始,NDK开始支持C++异常控制,需要手动打开
LOCAL_CPP_FEATURES += exceptions

include $(BUILD_EXECUTABLE)