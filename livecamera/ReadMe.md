本模块演示了在NDK中处理Bitmap,主要代码在decode方法中
包括：
头文件 #include <android/bitmap.h>
AndroidBitmap_getInfo() 获取bitmap信息

结构体AndroidBitmapInfo
typedef struct {
    uint32_t    width;  // Width in pixels
    uint32_t    height; // Height in pixels
    uint32_t    stride; // Number of bytes between each line
    int32_t     format; // Pixel structure (see AndroidBitmapFormat)
    uint32_t    flags;  // Unused for now
} AndroidBitmapInfo;

AndroidBitmap_lockPixels  操作bitmap时必须独占此对象，读写排他性

AndroidBitmap_unlockPixels()  释放锁



运行代码，移动摄像头，有明显延迟，表明这个代码远没有达到最优
可以从以下几个方面改进:
1、decode方法执行的算法(每一帧数据从YUV转成RGB)可以用RenderScript
2、采集视频，采用多个缓冲区
3、内存可以降低
4、代码采用多线程