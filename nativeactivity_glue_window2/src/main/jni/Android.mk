LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := native_glue

LS_CPP=$(subst $(1)/,,$(wildcard $(LOCAL_PATH)/*.cpp))
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
#or
LS_CPP=$(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES := $(LS_CPP:$(LOCAL_PATH)/%=%)

$(warning "the value of LOCAL_SRC_FILES is $(LOCAL_SRC_FILES)")

#使用__android_log_print需要添加
LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -llog -ljnigraphics -landroid

LOCAL_STATIC_LIBRARIES := android_native_app_glue

#NDK r5 版本开始,NDK开始支持C++异常控制,需要手动打开
LOCAL_CPP_FEATURES += exceptions

#对一些老版本的安卓需要放开下行，否则无法加载so
libsysv-hash-table-library_ldflags := Wl,-hash-style=sysv

include $(BUILD_SHARED_LIBRARY)
$(call import-module,android/native_app_glue)