1、管道
1）古老形式，是半双工的，数据只能在一个方向上流动，一个读，一个写。不过POSIX.1支持全双工管道。
2）只能在具有公共祖先的进程间使用，也能在同一个进程的线程间使用
3）写端关闭后，读端先读取所有数据，然后read返回0以示达到文件结束处
4）读端关闭，写端继续写，产生信号SIGPIPE,write返回-1，errno设置为EPIPE
5) 常量PIPE_BUF定义了内核中管道缓冲区大小

创建一个管道
#include <unistd.h>
int msgpipe[2];
pipe(msgpipe);//创建一个管道
readpipe = msgpipe[0];//读端文件描述符
writepipe = msgpipe[1];//写端文件描述符
当需要从父进程到子进程的IPC通道时，先按照上面方法创建管道，然后fork，然后父进程关闭readpipe，子进程关闭writepipe。

write(writepipe, msg, strlen(msg))//向管道写端写入数据
close(readpipe);//关闭管道读端

2、ALooper
通过源码我们知道ALooper只是包装了#include <utils/Looper.h>类
#include <android/looper.h>
ALooper* thelooper = ALooper_prepare(0);//如果当前线程已经有一个Looper就直接返回对象，否则初始化一个

int ret = ALooper_addFd(thelooper, readpipe, 1, ALOOPER_EVENT_INPUT, handle_message, NULL);
添加一个文件描述符，这样调用poll方法时可以通过文件描述符读到数据

ALooper_pollAll(-1, NULL, NULL, NULL);
这是poll方法，-1表示永久阻塞。一旦writepipe写入了数据，在poll函数中通过readpipe读出来，发给handle_message函数处理

ALooper_wake(thelooper);//唤醒阻塞中的poll方法

ALooper_removeFd(thelooper, readpipe);//ALooper_addFd的反向方法，移除对指定FD的监听

通过ALooper和pipe，实现了相当于android SDK中的Handler功能

3、互斥锁
在app这个模块中已经有讲解