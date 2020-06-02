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
#include "com_xue_firstndk_JniTest.h"


const char* long_to_string(long i) {
  std::stringstream result;
  result << i;
  return result.str().c_str();
}


/**
 * 从native返回一个String给Java
 * @param env
 * @param jclz
 * @return
 */
JNIEXPORT jstring JNICALL Java_com_xue_firstndk_JniTest_getString(JNIEnv *env, jclass jclz){
  return env->NewStringUTF("Hello 1");

}


/**
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    printHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_JniTest_printHello(JNIEnv *, jobject){
  __android_log_print(ANDROID_LOG_INFO, "TestNdk","Hello world");
  printf("Hello world!");
}

/**
 * 传入String转换为C类型的字符串
 * Class:     com_xue_firstndk_JniTest
 * Method:    printStr
 * Signature: (Ljava/lang/String;)V
 */
 extern "C"
JNIEXPORT void JNICALL Java_com_xue_firstndk_JniTest_printStr(JNIEnv *env, jobject, jstring jstr){
  const char* cstr = env->GetStringUTFChars(jstr,JNI_FALSE);
  if(cstr == NULL){
    std::cout<<"Param is NULL"<<std::endl;
    return ;
  }
  //cout看不到输出，可能是Android系统将stdout和stderr重定向到/dev/null
  std::cout<<cstr<<std::endl;
  __android_log_print(ANDROID_LOG_INFO,"TestNdk","%s",cstr);
  env->ReleaseStringUTFChars(jstr,cstr);



}
/**
 * 1、传入boolean转成C的bool类型
 * 2、C的bool转成jboolean返回给java
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incBoolean
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xue_firstndk_JniTest_reverseBoolean(JNIEnv * env, jobject thiz, jboolean val){
  //jboolean转bool
  bool b = val==JNI_FALSE;
  //bool转jboolean
  return b ? JNI_TRUE:JNI_FALSE;
}

/**
 *
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    toUpperChar
 * Signature: (C)C
 */
JNIEXPORT jchar JNICALL Java_com_xue_firstndk_JniTest_toUpperChar(JNIEnv* env, jobject thiz, jchar val){
  if(val >= 'a' && val <= 'z'){
    val -= ('a' - 'A');
  }
  return val;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incShort
 * Signature: (S)S
 */
JNIEXPORT jshort JNICALL Java_com_xue_firstndk_JniTest_incShort(JNIEnv * env, jclass clazz, jshort val){
  return ++val;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incInt
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_xue_firstndk_JniTest_createIntArr(JNIEnv* env, jobject thiz, jint len){
  jintArray intArr = env->NewIntArray(len);
  if(intArr == NULL){
    return NULL;
  }
  __android_log_print(ANDROID_LOG_INFO, "EEEEEEintarr","%p", &intArr);//%p 将&intArr当做地址打印
  jboolean b=JNI_FALSE;
  jint* iRR = env->GetIntArrayElements(intArr, &b);
  //方法一，通过遍历赋值
  for (int i = 0; i < len; ++i) {
    iRR[i] = i;
  }
  __android_log_print(ANDROID_LOG_INFO, "EEEEEEintarr2","%p", iRR);

  //方法二，通过SetIntArrayRegion赋值
//  jint* iRRNew = new jint[len];
//  iRRNew[len-1] = 5;
//  env->SetIntArrayRegion(intArr,0,len,iRRNew);

//  jintArray intArr2 = env->NewIntArray(len);
//  env->ReleaseIntArrayElements(intArr2, iRR, 0);//这两行测试表明，ReleaseIntArrayElements会将iRR的值赋给第一个参数

  env->ReleaseIntArrayElements(intArr, iRR, 0);//与GetIntArrayElements成对

  //将上一行(ReleaseIntArrayElements)注释掉，将方法二注释放开。观察java中打印结果，会发现iRRNew[len-1] = 5赋值有效
  return intArr;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incLong
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_xue_firstndk_JniTest_incLong(JNIEnv* env, jobject thiz, jlong val){
  return ++val;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    getFloat
 * Signature: (F)F
 */
JNIEXPORT jfloat JNICALL Java_com_xue_firstndk_JniTest_getFloat(JNIEnv* env, jobject thiz, jfloat f){
  return f;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    getDouble
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_com_xue_firstndk_JniTest_getDouble(JNIEnv* env, jobject thiz, jdouble d){
  return d;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    getClassName
 * Signature: (Ljava/lang/Class;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xue_firstndk_JniTest_charsToString(JNIEnv * env, jobject thiz, jcharArray chars){
  const jchar* jb = env->GetCharArrayElements(chars,JNI_FALSE);
  jsize len = env->GetArrayLength(chars);
  const char* log = long_to_string(len);

  __android_log_print(ANDROID_LOG_INFO, "EEEEEE","%s", log);
  jstring str = env->NewString(jb,len);
  if(str == NULL){
    return NULL;//OutOfMemoryError
  }
  env->ReleaseStringChars(str,jb);
  return str;
}

