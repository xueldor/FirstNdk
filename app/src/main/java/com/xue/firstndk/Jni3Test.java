package com.xue.firstndk;


import java.io.EOFException;

/**
 * 演示从native方法抛出java异常
 * 以及native调用的java方法抛出异常时如何处理
 */
public class Jni3Test {


    /**
     * 演示在native中抛出EOFException，并在java代码中捕获
     * 方法一
     */
    public native void throwEOFExpt() throws EOFException;


    /**
     * 演示在native中抛出EOFException，并在java代码中捕获
     * 方法二，更简洁的写法
     */
    public native void throwEOFExpt2() throws EOFException;

    /**
     * 在该方法中调用一个可能会抛异常的java方法
     * @throws EOFException
     */
    public native void checkJavaExpt();

    /**
     * 在native方法中调用可能会抛出异常的java方法
     * @throws EOFException
     */
    public void throwEofExpt() throws EOFException {
        throw new EOFException("java throw expt,check in cpp");
    }



    static {
        System.loadLibrary("JniLib");
    }


}
