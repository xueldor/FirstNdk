package com.xue.firstndk;

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
