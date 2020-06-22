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
#include <android/looper.h>
#include "com_xue_testalooper_MainActivity.h"

#ifdef __cplusplus
extern "C" {
#endif

ALooper *thelooper;
pthread_t loopID;

pthread_mutex_t looper_mutex_;

int readpipe;
int writepipe;

int handle_message(int fd, int events, void *data) {

    char buffer[100];
    memset(buffer, 0, 100);
    read(fd, buffer, sizeof(buffer));
    __android_log_print(ANDROID_LOG_INFO, "TestNativeLooper", "receive msg %s", buffer);
    return 1;
}
static void *threadRun(void *param) {
    __android_log_write(ANDROID_LOG_INFO, "TestNativeLooper", "createLooper in native thread");
    thelooper = ALooper_prepare(0);

    int msgpipe[2];
    pipe(msgpipe);//创建一个管道
    readpipe = msgpipe[0];//读端
    writepipe = msgpipe[1];//写端

    __android_log_write(ANDROID_LOG_INFO, "TestNativeLooper", "ALooper_addFd");
    int ret = ALooper_addFd(thelooper, readpipe, 1, ALOOPER_EVENT_INPUT, handle_message, NULL);

    ALooper_pollAll(-1, NULL, NULL, NULL);//-1:阻塞
    __android_log_write(ANDROID_LOG_INFO, "TestNativeLooper", "After ALooper_polled");
    ALooper_removeFd(thelooper, readpipe);
//    pthread_exit(NULL);//调用pthread_exit退出线程
/* or */    return (void*)0;
}

JNIEXPORT void JNICALL
Java_com_xue_testalooper_MainActivity_createLooper(JNIEnv *env, jobject jthis) {
    __android_log_write(ANDROID_LOG_INFO, "TestNativeLooper", "createLooper in java thread");
    thelooper = ALooper_prepare(0);
    __android_log_write(ANDROID_LOG_INFO, "TestNativeLooper", "looper prepared in java thread");
    ALooper_pollAll(3000, NULL, NULL, NULL);//阻塞3s
    __android_log_write(ANDROID_LOG_INFO, "TestNativeLooper", "End loop");
}

JNIEXPORT void JNICALL Java_com_xue_testalooper_MainActivity_createLooper2(JNIEnv *pEnv, jobject) {
    pthread_mutex_init(&looper_mutex_, NULL);//初始化互斥量

    pthread_create(&loopID, NULL, threadRun, NULL);//创建并执行子线程

    const char *msg = "abcd";
    int repeat = 10;
    while (repeat-- > 0) {
        pthread_mutex_lock(&looper_mutex_);//加锁。假设有多个线程向此管道写数据
        write(writepipe, msg, strlen(msg));//通过管道进行线程间通信
        pthread_mutex_unlock(&looper_mutex_);//释放锁

        sleep(1);
    }
    write(writepipe, "close", 5);//假设单个线程写，则无需加锁

    sleep(1);//等looper线程处理完回到阻塞状态，然后wake才有用
    ALooper_wake(thelooper);//ALooper_pollAll从阻塞中唤醒
    sleep(1);//等ALooper_removeFd执行再关闭管道

    if (readpipe != -1) {//关闭管道
        close(readpipe);
    }
    if (writepipe != -1) {
        close(writepipe);
    }
    pthread_mutex_destroy(&looper_mutex_);//销毁互斥量
}


#ifdef __cplusplus
}
#endif
