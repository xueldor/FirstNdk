#include <stdint.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <android/log.h>


#include <string>
#include "com_xue_firstndk_Jni3Test.h"

JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni3Test_throwEOFExpt(JNIEnv *env, jobject jthis){
    jclass class_EOFExpt = env->FindClass("java/io/EOFException");
    jmethodID id_EOFExpt = env->GetMethodID(class_EOFExpt,"<init>","()V");
    jthrowable obj_exc = (jthrowable)env->NewObject(class_EOFExpt,id_EOFExpt);
    env->Throw(obj_exc);//与java的throw语句不同，Throw方法不会中断本地方法的控制流，而是在方法返回后，java虚拟机抛出异常，因此Throw后应该立即跟着return语句
}

JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni3Test_throwEOFExpt2(JNIEnv *env, jobject jthis){
    //与java的throw语句不同，ThrowNew方法不会中断本地方法的控制流，在方法返回后，java虚拟机抛出异常，因此应该立即跟着return语句
    env->ThrowNew(env->FindClass("java/io/EOFException"),"出错啦");
}

JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni3Test_checkJavaExpt(JNIEnv *env, jobject jthis){
    jclass class_Jni3 = env->GetObjectClass(jthis);
    jmethodID id_thr = env->GetMethodID(class_Jni3,"throwEofExpt","()V");
    env->CallVoidMethod(jthis,id_thr);
    //C++的try语句没法捕获java方法抛出的异常，应该使用ExceptionOccurred判断
    jthrowable occur = env->ExceptionOccurred();
    if(occur == NULL){
        __android_log_print(ANDROID_LOG_INFO,"Jni3Lib ExceptionOccurred","No exception occured");
    }else{
        __android_log_print(ANDROID_LOG_INFO,"Jni3Lib ExceptionOccurred","exception occured");
    }
    //或者
    jboolean isoccur = env->ExceptionCheck();
    if(isoccur){
        __android_log_print(ANDROID_LOG_INFO,"Jni3Lib ExceptionCheck","exception occured");
    }else{
        __android_log_print(ANDROID_LOG_INFO,"Jni3Lib ExceptionCheck","No exception occured");
    }

    env->ExceptionClear();//消除异常，代码继续执行

    env->CallVoidMethod(jthis,id_thr);//不调用ExceptionClear，将异常传给java，java应该用try捕获
    return;
}
