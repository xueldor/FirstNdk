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
#include <unistd.h>
#include "com_xue_firstndk_Jni5Test.h"

typedef struct {
    int mStored;//在一个线程上面对mStored自增，java里面另外一个线程获取，演示加锁和释放锁
    JavaVM* mJavaVM;
    jobject mLock;
    pthread_t mThread;
    int32_t mRunning;
} StoreWatcher;


static jobject gLock;

/**
 * 创建LOCK对象，并赋给本地代码的gLock对象以及java代码中的LOCK对象
 * @param env
 * @param jthis
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni5Test_createLOCKObject(JNIEnv *env, jobject jthis) {
    jclass ObjectClass = env->FindClass("java/lang/Object");
    if (ObjectClass == NULL) abort();
    jmethodID ObjectConstructor = env->GetMethodID(ObjectClass,"<init>", "()V");
    if (ObjectConstructor == NULL) abort();
    jobject lockTmp = env->NewObject(ObjectClass, ObjectConstructor);
    env->DeleteLocalRef(ObjectClass);
    gLock = env->NewGlobalRef(lockTmp);
    env->DeleteLocalRef(lockTmp);

    jclass StoreThreadSafeClass = env->FindClass("com/xue/firstndk/Jni5Test");
    if (StoreThreadSafeClass == NULL) abort();
    jfieldID lockField = env->GetStaticFieldID(StoreThreadSafeClass,
                                               "LOCK", "Ljava/lang/Object;");
    if (lockField == NULL) abort();
    env->SetStaticObjectField(StoreThreadSafeClass, lockField, gLock);
    env->DeleteLocalRef(StoreThreadSafeClass);
}


void process(StoreWatcher* pWatcher){
    pWatcher->mStored++;
}

JNIEnv* getJNIEnv(JavaVM* pJavaVM) {
    JavaVMAttachArgs lJavaVMAttachArgs;
    lJavaVMAttachArgs.version = JNI_VERSION_1_6;
    lJavaVMAttachArgs.name = "NativeThread";
    lJavaVMAttachArgs.group = NULL;
    JNIEnv* lEnv;
    //POSIX线程不是Java平台的一部分，虚拟机不能识别，为了和Java空间交互，必须先附着到虚拟机上
    if (pJavaVM->AttachCurrentThread(&lEnv,&lJavaVMAttachArgs) != JNI_OK) {
        lEnv = NULL;
    }
    return lEnv;
}

void* runWatcher(void* pArgs){
    StoreWatcher* watcher = (StoreWatcher*) pArgs;

    JavaVM* javaVM = watcher->mJavaVM;
    JNIEnv* env = getJNIEnv(javaVM);
    if (env == NULL) abort();
    // Runs the thread loop.
    while (true) {
        //sleep(1); // In seconds.
        usleep(1000); // In microseconds,微秒。1000微秒==1毫秒
        env->MonitorEnter(watcher->mLock);//watcher->mLock等同Jni5Test.java中的LOCK对象
        if (!watcher->mRunning) break;
        process(watcher);
        env->MonitorExit(watcher->mLock);
    }
    javaVM->DetachCurrentThread();
    delete watcher;
    pthread_exit(NULL);
}


StoreWatcher* startWatcher(JavaVM* pJavaVM, jobject pLock) {
    StoreWatcher* watcher = new StoreWatcher();
    watcher->mJavaVM = pJavaVM;
    watcher->mStored = 1;
    watcher->mLock = pLock;
    watcher->mRunning = true;
    pthread_attr_t lAttributes;
    if (pthread_attr_init(&lAttributes)) abort();
    if (pthread_create(&watcher->mThread, &lAttributes,
                       runWatcher, watcher)) abort();
    return watcher;
}

void stopWatcher(StoreWatcher* pWatcher) {
    pWatcher->mRunning = false;
}

extern "C"
JNIEXPORT jlong JNICALL Java_com_xue_firstndk_Jni5Test_startWatcher(JNIEnv *pEnv, jobject jthis){
    JavaVM* javaVM;
    // Caches the VM.
    if (pEnv->GetJavaVM(&javaVM) != JNI_OK) abort();
    // Launches the background thread.
    StoreWatcher* watcher = startWatcher(javaVM, gLock);
    return (jlong) watcher;//在java端，用long类型保存native的地址
}

extern "C"
JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni5Test_stopWatcher(JNIEnv *, jobject, jlong pWatcher){
    stopWatcher((StoreWatcher*) pWatcher);
}


/*
 * Class:     com_xue_firstndk_Jni5Test
 * Method:    getInteger
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xue_firstndk_Jni5Test_getInteger(JNIEnv *, jobject, jlong watcher){
    StoreWatcher* pWatcher = (StoreWatcher*)watcher;
    return pWatcher->mStored;
}

/*
 * Class:     com_xue_firstndk_Jni5Test
 * Method:    setInteger
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni5Test_setInteger(JNIEnv *, jobject, jlong watcher, jint val){
    StoreWatcher* pWatcher = (StoreWatcher*)watcher;
    pWatcher->mStored = val;
}