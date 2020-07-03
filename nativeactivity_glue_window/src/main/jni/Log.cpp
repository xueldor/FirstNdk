#include "Log.h"

#include <stdarg.h>
#include <android/log.h>

void Log::info(const char *pMessage, ...) {
    va_list varArgs;
    va_start(varArgs,pMessage);
    __android_log_vprint(ANDROID_LOG_INFO,"TestNativeActivity",pMessage,varArgs);
    va_end(varArgs);
}
void Log::error(const char *pMessage, ...) {
    va_list varArgs;
    va_start(varArgs,pMessage);
    __android_log_vprint(ANDROID_LOG_ERROR,"TestNativeActivity",pMessage,varArgs);
    va_end(varArgs);
}
void Log::warn(const char *pMessage, ...) {
    va_list varArgs;
    va_start(varArgs,pMessage);
    __android_log_vprint(ANDROID_LOG_WARN,"TestNativeActivity",pMessage,varArgs);
    va_end(varArgs);
}
void Log::debug(const char *pMessage, ...) {
    va_list varArgs;
    va_start(varArgs,pMessage);
    __android_log_vprint(ANDROID_LOG_DEBUG,"TestNativeActivity",pMessage,varArgs);
    va_end(varArgs);
}