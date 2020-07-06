
#ifndef FIRSTNDK_GRAPHICSMANAGER_H
#define FIRSTNDK_GRAPHICSMANAGER_H

#include "Types.h"
#include <android_native_app_glue.h>

struct GraphicsElement{
    GraphicsElement(int32_t pWidth, int32_t pHeight):location(),width(pWidth),height(pHeight){}

    Location location;
    int32_t width;
    int32_t height;
};

class GraphicsManager {
public:
    GraphicsManager(android_app* pApplication);
    ~GraphicsManager();

    int32_t getRenderWidth(){
        return mRenderWidth;
    }
    int32_t getRenderHeight() {
        return mRenderHeight;
    }
    GraphicsElement* registerElement(int32_t pHeight,int32_t pWidth);
    status start();
    status update();

private:
    android_app* mApplication;
    int32_t mRenderWidth;
    int32_t mRenderHeight;
    GraphicsElement* mElements[1024];
    int32_t mElementCount;

};


#endif //FIRSTNDK_GRAPHICSMANAGER_H
