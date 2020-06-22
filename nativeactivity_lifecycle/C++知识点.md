函数的声明
1、float f();//声明一个函数f,f的定义在其他地方，返回float
float *f();//声明f, ()优先级高于*，所以返回float*

2、float (*f)();//声明了一个指针f,f指向一个函数，函数的格式如声明所示
将函数名称f、末尾的分号去掉，得到：
float (*)()
表示一个类型，与int、float一样表示类型，int表示一个整数，float表示浮点数，float (*)()表示“指向返回float的函数的指针”，
用此类型修饰变量名，就能得到这个“指向返回float的函数的指针”，如：
void (*b)();-->声明了b，b是函数指针，指向形如void funX()的函数，可以直接把funX赋给b
void (*b[10])(); -->声明了一个数组，数组长度为10，数组名为b，数组的元素是函数指针，指向形如void funX()的函数

3、函数定义：
  void sort(int a[], int n, int (*cmp)(int,int))//最后一个参数为函数指针类型参数
  {
  }
  因为函数声明可以省略参数的名称，所以可以这样声明:
  void sort(int[], int, int (*)(int,int))

4、最后分析一下void (*b[10])(void (*)());
*b[10] -->b是一个有10个元素的数组，每个元素都是指针
最右边的括号(void (*)())中没有出现变量名，所以代表一个类型，即“指向返回值为void的函数的指针，且函数没有参数”
(void (*)())出现在void (*b[10])的右边，表示声明了函数，函数的参数类型是void (*)()，即参数是函数指针
结论： b数组，长度10，每一个元素都是函数指针，这个函数有一个参数，参数又是一个函数指针。

这种写法有耍人的嫌疑，我们可以用typedef来给复杂的类型定义别名，达到简化的目的：
typedef void (*pFunParam)();//void (*)()是类型，pFunParam是起得别名。
这样，void (*b)(); 可以简写为pFunParam b;

最后，对整个表达式：
typedef void (*pFun)(pFunParam);//void (*)(pFunParam)是类型，pFun是此类型的别名，类型pFun表示一个函数指针，且此函数的参数类型是pFunParam,也就是void (*)()

总结typedef用途
1、同时声明指针型的多个对象。比如
    char* pa, pb; // pa是指针，pb是普通char类型，不符合我们的意图
    以下则可行：
    typedef char* PCHAR;
    PCHAR pa, pb;

2、在旧的C代码中，帮助struct。C代码中声明struct新对象时，必须要带上struct。通过typedef简化。在C++中，这种用途意义不大，理解它只是为了掌握以前的代码

3、用typedef来定义与平台无关的类型
比如定义一个叫 REAL 的浮点类型，在:
平台一上，让它表示最高精度的类型为：
    typedef long double REAL;
在不支持 long double 的平台二上，改为：
    typedef double REAL;
在连 double 都不支持的平台三上，改为：
    typedef float REAL;

也就是说，当跨平台时，只要改下 typedef 本身就行，不用对其他源码做任何修改。
标准库就广泛使用了这个技巧，比如size_t。另外，因为typedef是定义了一种类型的新别名，不是简单的字符串替换，所以它比宏来得稳健。

4、为复杂的声明定义一个新的简单的别名
方法是：在原来的声明里逐步用别名替换一部分复杂声明，如此循环，把带变量名的部分留到最后替换，得到的就是原声明的最简化版。举例：
原声明：void (*b[10]) (void (*)());
新:
typedef void (*pFunParam)();
typedef void (*pFunx)(pFunParam);
pFunx b[10];
前面已经分析过这个例子