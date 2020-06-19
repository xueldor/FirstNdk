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

同时还有jni目录下的Android.mk、Application.mk文件编写

打印log：
#include <android/log.h>
print方法可以格式化字符串，参考ANSI C的printf方法
__android_log_print(ANDROID_LOG_INFO,"Jni2Lib","NewGlobalRef %d",22);//ANDROID_LOG_INFO:级别为info；Jni2Lib：log tag；参考java Log类的log方法
write方法：
__android_log_write(ANDROID_LOG_INFO,"Jni2Lib","NewGlobalRef");//向log输出简单字符串
同时Android.mk中加入LOCAL_LDLIBS+=-llog

关于Jni5Lib.cpp中出现的POSIX线程
1、通过pthread_create函数创建
2、pthread_attr_t指定新线程的栈基址、栈大小、守护大小、调度策略、调度优先级等，一般传NULL使用默认值即可
3、POSIX线程不是Java平台的一部分，虚拟机不能识别，为了和Java空间交互，必须先附着到虚拟机上,通过:
    pJavaVM->AttachCurrentThread(&lEnv,&lJavaVMAttachArgs)方法
4、javaVM->DetachCurrentThread();从java虚拟机中分离当前线程
所以，在子线程中执行native代码有两种方法：java创建Thread，在Thread中调用native方法；在C中通过pthread_create创建子线程然后attach到虚拟机

关于互斥锁和信号量
Jni5Test演示了用java的synchronized同步java和C代码的方法。其实还可以用Linux中的互斥锁
#include <pthread.h>//包含头文件
pthread_mutex_t looper_mutex_;//声明互斥实例
pthread_mutex_init(&looper_mutex_, NULL);//初始化
pthread_mutex_lock(&looper_mutex_);//加锁
pthread_mutex_unlock(&looper_mutex_);//解锁
pthread_mutex_destroy(&looper_mutex_);//销毁锁

信号量：互斥锁同一时间只能有一个线程持有锁。信号量不同，只要value大于0，其他线程就可以sem_wait成功，否则线程阻塞
#include <semaphore.h>
int sem_init(sem_t *sem, int pshared, unsigned int value)//初始化信号量
int sem_post(sem_t * sem)//信号量的value加一，表示增加一个可访问的资源
int sem_wait(sem_t * sem)//将信号灯原子地减1，或者阻塞
int sem_trywait(sem_t * sem)
int sem_getvalue(sem_t * sem, int * sval)//读取sem中的灯计数，存于*sval中，并返回0。
int sem_destroy(sem_t * sem)//销毁