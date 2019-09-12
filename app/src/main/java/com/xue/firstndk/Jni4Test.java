package com.xue.firstndk;

/**
 * 演示JNI函数动态注册
 */
public class Jni4Test {
    static {
        System.loadLibrary("JniLib");
    }
    public static native void printHello();
    public static native void printWorld();
}
