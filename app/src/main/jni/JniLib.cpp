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


JNIEXPORT jstring JNICALL Java_com_xue_firstndk_JniTest_getString
        (JNIEnv *env, jclass jclz){
  return env->NewStringUTF("Hello 1");

}


/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    printHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_JniTest_printHello
        (JNIEnv *, jobject){
  __android_log_print(ANDROID_LOG_INFO, "TestNdk","Hello world");
  printf("Hello world!");
}

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    printStr
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_JniTest_printStr(JNIEnv *env, jobject, jstring jstr){
  const char* cstr = env->GetStringUTFChars(jstr,JNI_FALSE);
  if(cstr == NULL){
    std::cout<<"Param is NULL"<<std::endl;
    return ;
  }
  std::cout<<cstr<<std::endl;
  env->ReleaseStringUTFChars(jstr,cstr);



}
/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incBoolean
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xue_firstndk_JniTest_reverseBoolean
        (JNIEnv * env, jobject thiz, jboolean val){
  //jboolean转bool
  bool b = val==JNI_FALSE;
  //bool转jboolean
  return b ? JNI_TRUE:JNI_FALSE;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    toUpperChar
 * Signature: (C)C
 */
JNIEXPORT jchar JNICALL Java_com_xue_firstndk_JniTest_toUpperChar
        (JNIEnv* env, jobject thiz, jchar val){
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
JNIEXPORT jshort JNICALL Java_com_xue_firstndk_JniTest_incShort
        (JNIEnv * env, jclass clazz, jshort val){
  return ++val;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incInt
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_xue_firstndk_JniTest_createIntArr
        (JNIEnv* env, jobject thiz, jint len){
  jintArray intArr = env->NewIntArray(len);
  if(intArr == NULL){
    return NULL;
  }
  jboolean b=JNI_TRUE;
  jint* iRR = env->GetIntArrayElements(intArr, &b);
  for (int i = 0; i < len; ++i) {
    iRR[i] = i;
  }
  env->ReleaseIntArrayElements(intArr, iRR, 0);
  return intArr;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    incLong
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_xue_firstndk_JniTest_incLong
        (JNIEnv* env, jobject thiz, jlong val){
  return ++val;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    getFloat
 * Signature: (F)F
 */
JNIEXPORT jfloat JNICALL Java_com_xue_firstndk_JniTest_getFloat
        (JNIEnv* env, jobject thiz, jfloat f){
  return f;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    getDouble
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_com_xue_firstndk_JniTest_getDouble
        (JNIEnv* env, jobject thiz, jdouble d){
  return d;
}

/*
 * Class:     com_xueldor_testndk_Printf_Jni
 * Method:    getClassName
 * Signature: (Ljava/lang/Class;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xue_firstndk_JniTest_charsToString
        (JNIEnv * env, jobject thiz, jcharArray chars){
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

