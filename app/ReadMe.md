本模块演示jni的最基础的使用方法：
java2Head.bat & JniTest.java & JniLib.cpp :
演示从java中的native方法声明，生成对应的.h文件；C/C++中对应native方法的格式；
演示基本数据类型通过参数从java传递给C的方法；基本数据类型的数组的传递方法；
演示C方法返回基本类型的数据给java的方法

Jni2Test.java & Jni2Lib.cpp :
演示从C代码中获取和修改java的字段；演示C代码调用java中的方法

Jni3Test.java & Jni3Lib.cpp :
演示C代码中创建java类型的异常对象，并将异常抛给java；
演示C代码调用一个java的方法，当该java方法抛出异常时的处理方法；

Jni4Test.java & Jni4Lib.cpp :
演示使用动态注册方法注册JNI函数，也就是通过代码将java native方法与C++的函数绑定

Jni5Test.java & Jni5Lib.cpp :
演示用MonitorEnter和MonitorExit实现java方法和native方法的线程同步