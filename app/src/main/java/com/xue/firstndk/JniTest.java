package com.xue.firstndk;

/**
 * 演示参数传递和返回
 * C有int和long，java也有int和long，但是不能简单划等号
 * java的int总是32位，而C取决于平台，可能是16位，也可能是32位
 * 因此在jni.h里定义了jboolean、jbyte、jchar、jshort等类型，
 * 根据平台的不同，通过typedef语句对应到C语言的基本类型
 * 比如在32位的机器上，定义为typedef int32_t  jint
 * 在16位的机器上，定义可能就是typedef int16_t  jint;
 * 因此注意在不同平台上，jni.h和jni_md.h不能通用
 */
public class JniTest {
    static {
        System.loadLibrary("JniLib");
    }

    public static native String getString();

    public native void printHello();

    public native void printStr(String str);

    public native boolean reverseBoolean(boolean b);

    public native char toUpperChar(char c);

    public native static short incShort(short s);

    public native int[] createIntArr(int len);

    public native long incLong(long l);

    public native float getFloat(float f);

    public native double getDouble(double d);

    public native String charsToString(char[] chars);
}
