
#ifndef FIRSTNDK_GRAPHICSMANAGER_H
#define FIRSTNDK_GRAPHICSMANAGER_H

#include "Resource.h"
#include "Types.h"
#include <android_native_app_glue.h>
//绑定OpenGl ES和android平台
#include <EGL/egl.h>
//渲染图形
#include <GLES2/gl2.h>

struct GraphicsElement{
    GraphicsElement(int32_t pWidth, int32_t pHeight):location(),width(pWidth),height(pHeight){}

    Location location;
    int32_t width;
    int32_t height;
};

struct TextureProperties {
    Resource* textureResource;
    GLuint texture;
    int32_t width;
    int32_t height;
};


class GraphicsComponent {
public:
    virtual status load() = 0;
    virtual void draw() = 0;
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

    status start();
    void stop();
    status update();

    TextureProperties* loadTexture(Resource& pResource);

private:
    android_app* mApplication;
    int32_t mRenderWidth;
    int32_t mRenderHeight;
    EGLDisplay mDisplay;
    EGLSurface mSurface;
    EGLContext mContext;

    GLfloat mProjectionMatrix[4][4];

    TextureProperties mTextures[32];
    int32_t mTextureCount;
};

#endif //FIRSTNDK_GRAPHICSMANAGER_H
