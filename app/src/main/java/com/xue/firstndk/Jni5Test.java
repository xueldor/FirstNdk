package com.xue.firstndk;

/**
 * 演示java方法与C函数之间的线程同步
 * 有两种方法：native互斥量(POSIX mutexes)；java synchronized.
 * 本示例演示后一种。本质上java同步内部实现也是POSIX primitives
 */
public class Jni5Test {
    protected static Object LOCK;
    private long pWatcher;

    static {
        System.loadLibrary("JniLib");
    }
    //将LOCK对象传给C，这样本地代码才能加锁
    public native void createLOCKObject();

    private native long startWatcher();
    private native void stopWatcher(long pPointer);

    private native synchronized int getInteger(long pPointer);
    private native synchronized void setInteger(long pPointer,int pInt);



    public int getInteger0(){
        synchronized (LOCK) {
            if(pWatcher != 0) {
                return getInteger(pWatcher);
            }
        }
        return -1;
    }

    public void setInteger0( int pInt) {
        synchronized (LOCK) {
            if(pWatcher != 0) {
                setInteger(pWatcher, pInt);
            }
        }
    }
    public void startWatcher0() {
        synchronized (LOCK) {
            pWatcher = startWatcher();
        }
    }

    public void stopWatcher0() {
        synchronized (LOCK) {
            if(pWatcher != 0) {
                stopWatcher(pWatcher);
                pWatcher = 0;
            }
        }
    }

}
