//
// Created by xue on 2020/7/2.
//

#include <cstring>
#include "GraphicsManager.h"
#include "Log.h"

GraphicsManager::GraphicsManager(android_app *pApplication):
        mApplication(pApplication),
        mRenderWidth(0), mRenderHeight(0),
        mElements(),mElementCount(0){
    Log::info("Creating GraphicsManager.");
}
GraphicsManager::~GraphicsManager() {
    Log::info("Destroying GraphicsManager.");
    for(int32_t i = 0;i< mElementCount; ++i){
        delete mElements[i];
    }
}

GraphicsElement* GraphicsManager::registerElement(int32_t pHeight, int32_t pWidth) {
    mElements[mElementCount] = new GraphicsElement(pHeight,pWidth);
    return mElements[mElementCount++];//返回刚new的对象，并自增count
}

status GraphicsManager::start() {
    Log::info("Starting GraphicsManager.");
    ANativeWindow_Buffer windowBuffer;
    //设置window格式是32bits。width和height会被忽略，因为传的不是正值,这种情况下window的width和height是屏幕大小
    //RGBX means, that the pixel format still has an alpha channel, but it is ignored, and is always set to 255.
    if(ANativeWindow_setBuffersGeometry(mApplication->window,0,0,WINDOW_FORMAT_RGBX_8888) < 0){
        Log::error("Error while setting buffer geometry.");
        return STATUS_KO;
    }
    //在lock方法中，buffer会被填充
    if(ANativeWindow_lock(mApplication->window,&windowBuffer,NULL) >= 0){
        Log::info("windowBuffer width=%d,heidth=%d,stride=%d",windowBuffer.width,windowBuffer.height,windowBuffer.stride);
        mRenderWidth = windowBuffer.width;
        mRenderHeight = windowBuffer.height;
        ANativeWindow_unlockAndPost(mApplication->window);
    }else {
        Log::error("Error while locking window.");
        return STATUS_KO;
    }
    return STATUS_OK;
}

status GraphicsManager::update() {
    ANativeWindow_Buffer windowBuffer;
    if (ANativeWindow_lock(mApplication->window, &windowBuffer, NULL) < 0) {
        Log::error("Error while starting GraphicsManager");
        return STATUS_KO;
    }
    //stride: buffer中一行的像素个数。行 * 高 * 一个像素的字节数
    memset(windowBuffer.bits,0,windowBuffer.stride * windowBuffer.height * sizeof(uint32_t*));

    Log::info("buffer addr = %p",&windowBuffer.bits);//地址是不会变的

    int32_t maxX = windowBuffer.width - 1;
    int32_t maxY = windowBuffer.height - 1;
    for (int32_t i = 0; i < mElementCount; ++i) {
        GraphicsElement* element = mElements[i];

        int32_t leftX = element->location.x - element->width/2;
        int32_t rightX = element->location.x + element->width/2;
        int32_t leftY = windowBuffer.height - element->location.y - element->height/2;
        int32_t rightY = windowBuffer.height - element->location.y + element->height/2;

        //防止越界
        if(rightX < 0 || leftX > maxX || rightY < 0 || leftY > maxY)continue;
        if (leftX < 0) leftX = 0;
        else if (rightX > maxX) rightX = maxX;
        if (leftY < 0) leftY = 0;
        else if (rightY > maxY) rightY = maxY;

        Log::info("bits leftX=%d,leftY=%d,rightX=%d,rightY=%d",leftX,leftY,rightX,rightY);

        uint32_t* line = (uint32_t*) (windowBuffer.bits) + (windowBuffer.stride * leftY);
        for(int iY = leftY;iY <= rightY; iY++){
            for (int iX = leftX; iX <= rightX; iX++) {
                line[iX] = 0x000000FF;//RED
//                line[iX] = 0x0000FF00;//green
//                line[iX] = 0x00FF0000;//blue
            }
            line = line + windowBuffer.stride;
        }
    }
    ANativeWindow_unlockAndPost(mApplication->window);//unlock后界面立即刷新
    return STATUS_OK;
}