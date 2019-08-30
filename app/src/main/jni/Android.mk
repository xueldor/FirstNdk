LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := JniLib
LOCAL_SRC_FILES =: Jni2Lib.cpp JniLib.cpp

#使用__android_log_print需要添加
LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -llog

include $(BUILD_SHARED_LIBRARY)