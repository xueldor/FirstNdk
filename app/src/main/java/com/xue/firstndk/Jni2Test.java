package com.xue.firstndk;

import android.util.Log;

/**
 * 演示从cpp操作java的字段和方法
 */
public class Jni2Test {
    private int salary;
    private static String name = "zhangsan";

    /**
     * 演示在C中获取和修改java类中int类型字段的值
     * 在native方法中操作salary对象
     * @param raise
     */
    public native void raiseSalary(int raise);

    /**
     * 演示在C中获取java类中static修饰的字段
     * 在native方法中获取String类型的name的值
     */
    public native void printName();

    /**
     * 演示在C中回调java方法，并且此方法有一个重载方法
     * @param i
     */
    public void onProgress(int i){
        System.out.println("progress " + i);

    }

    /**
     * 演示在C中回调java的static方法
     * @param prog
     */
    public static boolean onProgress(long prog){
        System.out.println("progress2 " + prog);
        return true;
    }

    /**
     * 演示在C中回调java的方法
     */
    public void onFinish(){
        System.out.println("call onFinish in CPP");
        Log.i("Jni2Java","call onFinish in CPP");
    }

    /**
     *在C实现的doTask中回调java方法
     */
    public native void doTask();


    /**
     * 用C构造Jni2Test的对象
     * @return
     */
    public static native Jni2Test createInstance();


    //注释掉，改用native方法实现同样功能
//    public void raiseSalary(int raise){
//        salary += raise;
//    }

    static {
        System.loadLibrary("JniLib");
    }

    public int getSalary() {
        return salary;
    }
}
