/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_xue_firstndk_JniTest */

#ifndef _Included_com_xue_firstndk_JniTest
#define _Included_com_xue_firstndk_JniTest
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    getString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xue_firstndk_JniTest_getString
  (JNIEnv *, jclass);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    printHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_JniTest_printHello
  (JNIEnv *, jobject);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    printStr
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_xue_firstndk_JniTest_printStr
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    reverseBoolean
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xue_firstndk_JniTest_reverseBoolean
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    toUpperChar
 * Signature: (C)C
 */
JNIEXPORT jchar JNICALL Java_com_xue_firstndk_JniTest_toUpperChar
  (JNIEnv *, jobject, jchar);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    incShort
 * Signature: (S)S
 */
JNIEXPORT jshort JNICALL Java_com_xue_firstndk_JniTest_incShort
  (JNIEnv *, jclass, jshort);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    createIntArr
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_xue_firstndk_JniTest_createIntArr
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    incLong
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_xue_firstndk_JniTest_incLong
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    getFloat
 * Signature: (F)F
 */
JNIEXPORT jfloat JNICALL Java_com_xue_firstndk_JniTest_getFloat
  (JNIEnv *, jobject, jfloat);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    getDouble
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_com_xue_firstndk_JniTest_getDouble
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     com_xue_firstndk_JniTest
 * Method:    charsToString
 * Signature: ([C)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xue_firstndk_JniTest_charsToString
  (JNIEnv *, jobject, jcharArray);

#ifdef __cplusplus
}
#endif
#endif
