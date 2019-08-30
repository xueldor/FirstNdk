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
#include "com_xue_firstndk_Jni2Test.h"

static jclass class_Test1 = 0;

JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni2Test_raiseSalary(JNIEnv *env, jobject jthis, jint raise){
    //根据类实例获取类的Class对象,类似java中this.getClass()
    jclass class_Jni2Text = env->GetObjectClass(jthis);//类引用只在本方法return之前有效
    //获取字段Id,类似java通过反射获取Field对象:Jni2Test.class.getField("salary")
    jfieldID id_salary = env->GetFieldID(class_Jni2Text,"salary","I");

    //类似java通过反射获取字段的值:salaryField.getInt(this)
    jint salary = env->GetIntField(jthis,id_salary);
    salary += raise;

    //设置属性的值
    env->SetIntField(jthis,id_salary,salary);


    //如果想引用类，不局限在本方法
    if(class_Test1 == 0){
        class_Test1 = (jclass)env->NewGlobalRef(class_Jni2Text);
        __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","NewGlobalRef");
    }else{
        __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","class_Test1 is not null");
    }
    env->DeleteGlobalRef(class_Test1);//必须手动释放
    class_Test1 = NULL;//释放后务必将变量指向0，这是C和Cpp的基本常识

}

JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni2Test_printName(JNIEnv *env, jobject jthis){
    //获取java中static属性的值
    jclass class_jni2 = env->FindClass("com/xue/firstndk/Jni2Test");//获取class
    if(class_jni2 == 0){
        __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","class_string is null");
    }
    jfieldID id_name = env->GetStaticFieldID(class_jni2,"name","Ljava/lang/String;");//获取field id,String后面有个分号
    if(id_name == 0){
        __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","id_name is null");
    }
    jstring name = (jstring)env->GetStaticObjectField(class_jni2,id_name);
    const char* strName = env->GetStringUTFChars(name,JNI_FALSE);
    __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","%s",strName);
}

/*
 * Class:     com_xue_firstndk_Jni2Test
 * Method:    doTask
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_Jni2Test_doTask(JNIEnv *env, jobject jthis){
    jclass class_jni2 = env->GetObjectClass(jthis);//or use FindClass

    jmethodID method_onprogressI = env->GetMethodID(class_jni2,"onProgress","(I)V");
    jmethodID method_onprogressJ = env->GetStaticMethodID(class_jni2,"onProgress","(J)Z");
    jmethodID method_onfinish = env->GetMethodID(class_jni2,"onFinish","()V");

    if(method_onfinish == 0){
        __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","method_onfinish is null");
    }else{
        env->CallVoidMethod(jthis,method_onprogressI,2);
        jboolean succ = env->CallStaticBooleanMethod(class_jni2,method_onprogressJ,2L);
        __android_log_print(ANDROID_LOG_INFO,"Jni2Lib","onprogress2 return is %d",succ);
        env->CallVoidMethod(jthis,method_onfinish);
    }

}

JNIEXPORT jobject JNICALL Java_com_xue_firstndk_Jni2Test_createInstance(JNIEnv *env, jclass jclz){
    jclass class_jni2 = env->FindClass("com/xue/firstndk/Jni2Test");
    jmethodID id_jni2 = env->GetMethodID(class_jni2,"<init>","()V");
    jobject jni2 = env->NewObject(class_jni2,id_jni2);
    return jni2;
}

/**
 *数据类型的编码方案：
 * B    byte
 * C    char
 * D    double
 * F    float
 * I    int
 * J    long
 * Lclassname;    类
 * S    short
 * V    void
 * Z    boolean
 * 特殊的有
 * long，编码是J
 * boolean,编码是Z
 *
 * 非基本类型，用全称,点号改为斜杠，放在L和分号之间，如
 * Ljava/lang/String;    java.lang.String
 *
 * 一维数组前面加左方括号：
 * [Ljava/lang/String;   String[]
 *
 * 二维数组前面加两个左方括号:
 * [[F    float[][]
 *
 *
*/