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

#ifdef __cplusplus
extern "C" {
#endif

int main(){
    printf("Test printf %d\n,test",1);//打印到控制台
    //打印到Logcat
    __android_log_print(ANDROID_LOG_INFO,"Test Log","it's log");
}


#ifdef __cplusplus
}
#endif
