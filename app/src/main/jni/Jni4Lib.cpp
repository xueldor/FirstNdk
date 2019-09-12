#include <jni.h>
#include <android/log.h>

void com_xue_firstndk_Jni4Test_printHello(JNIEnv *env, jobject jthis){
    __android_log_print(ANDROID_LOG_INFO,"Jni4Test","Hello");
}
void com_xue_firstndk_Jni4Test_printWorld(JNIEnv *env, jobject jthis){
    __android_log_print(ANDROID_LOG_INFO,"Jni4Test","World");
}

static JNINativeMethod gMethods[] = {
        {
            "printHello",
            "()V",
            (void*)com_xue_firstndk_Jni4Test_printHello
        },
        {
            "printWorld",
            "()V",
            (void*)com_xue_firstndk_Jni4Test_printWorld
        }
};

int jniRegisterNativeMethods(JNIEnv* env,const char* className,const JNINativeMethod* gMethods,int numMethods){
    jclass clazz = env->FindClass(className);
    if(env->RegisterNatives(clazz,gMethods,numMethods) < 0){
        return -1;
    }
    return 0;
}

/**
 * java层通过System.loadLibrary加载完so后会紧接着查找JNI_OnLoad函数
 * 所以可以在JNI_OnLoad函数中注册native方法
 * @param vm 自动传入
 * @return 必须返回JNI_VERSION_1_4，否则报错。
 *         如果注册失败就返回-1让系统报错退出
 */
jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    if(vm->GetEnv((void**)&env,JNI_VERSION_1_4)!= JNI_OK){
        return -1;
    }
    if(jniRegisterNativeMethods(env,"com/xue/firstndk/Jni4Test",gMethods, sizeof(gMethods)/ sizeof(gMethods[0])) == 0){
        return JNI_VERSION_1_4;
    }
    return -1;

}