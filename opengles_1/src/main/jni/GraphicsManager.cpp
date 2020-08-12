//
// Created by xue on 2020/7/2.
//

#include <cstring>
#include "GraphicsManager.h"
#include "Log.h"
#include <png.h>
#include <setjmp.h>

GraphicsManager::GraphicsManager(android_app *pApplication):
        mApplication(pApplication),
        mRenderWidth(0), mRenderHeight(0),
        mDisplay(EGL_NO_DISPLAY),mSurface(EGL_NO_SURFACE),mContext(EGL_NO_CONTEXT),
        mProjectionMatrix(),
        mTextures(), mTextureCount(0){
    Log::info("Creating GraphicsManager.");
}

GraphicsManager::~GraphicsManager() {
    Log::info("Destroying GraphicsManager.");
}

void callback_readPng(png_structp pStruct,
                      png_bytep pData, png_size_t pSize) {
    Resource* resource = ((Resource*) png_get_io_ptr(pStruct));
    if (resource->read(pData, pSize) != STATUS_OK) {
        resource->close();
    }
}

status GraphicsManager::start() {
    Log::info("Starting GraphicsManager.");
    EGLint format,numConfigs,errorResult;
    GLenum status;
    EGLConfig config;

    const EGLint DISPLAY_ATTRIBS[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                                      EGL_BLUE_SIZE,5,EGL_GREEN_SIZE,6,EGL_RED_SIZE,5,
                                      EGL_SURFACE_TYPE,EGL_WINDOW_BIT,EGL_NONE
    };
    const EGLint CONTEXT_ATTRIBS[] = {
            EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE
    };
    mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(mDisplay == EGL_NO_DISPLAY) goto ERROR;

    if(!eglInitialize(mDisplay,NULL,NULL)) goto ERROR;

    if(!eglChooseConfig(mDisplay, DISPLAY_ATTRIBS, &config, 1,
                        &numConfigs) || (numConfigs <= 0)) goto ERROR;

    if (!eglGetConfigAttrib(mDisplay, config,
                            EGL_NATIVE_VISUAL_ID, &format)) goto ERROR;
    if(ANativeWindow_setBuffersGeometry(mApplication->window,0,0,format) < 0){
        Log::error("Error while setting buffer geometry.");
        goto ERROR;
    }

    mSurface = eglCreateWindowSurface(mDisplay,config,mApplication->window,NULL);
    if (mSurface == EGL_NO_SURFACE) goto ERROR;

    mContext = eglCreateContext(mDisplay, config, NULL,CONTEXT_ATTRIBS);

    if (mContext == EGL_NO_CONTEXT) goto ERROR;

    if(!eglMakeCurrent(mDisplay,mSurface,mSurface,mContext)
        || !eglQuerySurface(mDisplay,mSurface,EGL_WIDTH,&mRenderWidth)
        || !eglQuerySurface(mDisplay,mSurface,EGL_HEIGHT,&mRenderHeight)
        || (mRenderWidth <= 0) || (mRenderHeight <= 0)) goto ERROR;

    glViewport(0,0,mRenderWidth,mRenderHeight);
    glDisable(GL_DEPTH_TEST);

    memset(mProjectionMatrix[0], 0, sizeof(mProjectionMatrix));
    mProjectionMatrix[0][0] =  2.0f / GLfloat(mRenderWidth);
    mProjectionMatrix[1][1] =  2.0f / GLfloat(mRenderHeight);
    mProjectionMatrix[2][2] = -1.0f; mProjectionMatrix[3][0] = -1.0f;
    mProjectionMatrix[3][1] = -1.0f; mProjectionMatrix[3][2] =  0.0f;
    mProjectionMatrix[3][3] =  1.0f;

    return STATUS_OK;


    ERROR:
    Log::error("Error while starting GraphicsManager");
    stop();
    return STATUS_KO;
}

void GraphicsManager::stop() {
    Log::info("Stopping GraphicsManager.");
    for(int32_t i = 0;i < mTextureCount;++i){
        glDeleteTextures(1,&mTextures[i].texture);
    }
    mTextureCount = 0;

    if(mDisplay != EGL_NO_DISPLAY){
        eglMakeCurrent(mDisplay,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
        if(mContext != EGL_NO_CONTEXT){
            eglDestroyContext(mDisplay,mContext);
            mContext = EGL_NO_CONTEXT;
        }
        if(mSurface != EGL_NO_SURFACE){
            eglDestroySurface(mDisplay,mSurface);
            mSurface = EGL_NO_SURFACE;
        }
        eglTerminate(mDisplay);
        mDisplay = EGL_NO_DISPLAY;
    }
}

TextureProperties* GraphicsManager::loadTexture(Resource &pResource) {
    for(int32_t i = 0;i < mTextureCount; ++i){
        if(pResource == *mTextures[i].textureResource){
            Log::info("Found %s in cache",pResource.getPath());
            return &mTextures[i];
        }
    }
    Log::info("Loading texture %s", pResource.getPath());
    TextureProperties* textureProperties;
    GLuint texture;
    GLint format;
    png_byte header[8];
    png_structp pngPtr = NULL;
    png_infop infoPtr = NULL;

    png_byte* image = NULL;
    png_bytep* rowPtrs = NULL;

    png_int_32 rowSize;
    bool transparency;

    if (pResource.open() != STATUS_OK) goto ERROR;
    Log::info("Checking signature.");
    if (pResource.read(header, sizeof(header)) != STATUS_OK)
        goto ERROR;
    if (png_sig_cmp(header, 0, 8) != 0) goto ERROR;

    Log::info("Creating required structures.");
    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                    NULL, NULL, NULL);
    if (!pngPtr) goto ERROR;
    infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) goto ERROR;

    png_set_read_fn(pngPtr, &pResource, callback_readPng);

    if (setjmp(png_jmpbuf(pngPtr))) goto ERROR;

    png_set_sig_bytes(pngPtr, 8);
    png_read_info(pngPtr, infoPtr);
    png_int_32 depth, colorType;
    png_uint_32 width, height;
    png_get_IHDR(pngPtr, infoPtr, &width, &height,
                 &depth, &colorType, NULL, NULL, NULL);

    transparency = false;
    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(pngPtr);
        transparency = true;
    }

    if (depth < 8) {
        png_set_packing (pngPtr);
        // Shrinks PNG with 16bits per color channel down to 8bits.
    } else if (depth == 16) {
        png_set_strip_16(pngPtr);
    }

    switch (colorType) {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(pngPtr);
            format = transparency ? GL_RGBA : GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB:
            format = transparency ? GL_RGBA : GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGBA:
            format = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_GRAY:
            png_set_expand_gray_1_2_4_to_8(pngPtr);
            format = transparency ? GL_LUMINANCE_ALPHA:GL_LUMINANCE;
            break;
        case PNG_COLOR_TYPE_GA:
            png_set_expand_gray_1_2_4_to_8(pngPtr);
            format = GL_LUMINANCE_ALPHA;
            break;
    }
    png_read_update_info(pngPtr, infoPtr);

    rowSize = png_get_rowbytes(pngPtr, infoPtr);
    if (rowSize <= 0) goto ERROR;
    // Ceates the image buffer that will be sent to OpenGL.
    image = new png_byte[rowSize * height];
    if (!image) goto ERROR;
    // Pointers to each row of the image buffer. Row order is
    // inverted because different coordinate systems are used by
    // OpenGL (1st pixel is at bottom left) and PNGs (top-left).
    rowPtrs = new png_bytep[height];
    if (!rowPtrs) goto ERROR;
    for (int32_t i = 0; i < height; ++i) {
        rowPtrs[height - (i + 1)] = image + i * rowSize;
    }

    png_read_image(pngPtr, rowPtrs);
    // Frees memory and resources.
    pResource.close();
    png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
    delete[] rowPtrs;

    GLenum errorResult;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set-up texture properties.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, image);
    // Finished working with the texture.
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] image;
    if (glGetError() != GL_NO_ERROR) goto ERROR;
    Log::info("Texture size: %d x %d", width, height);

    textureProperties = &mTextures[mTextureCount++];
    textureProperties->texture = texture;
    textureProperties->textureResource = &pResource;
    textureProperties->width = width;
    textureProperties->height = height;
    return textureProperties;

    ERROR:
        Log::error("Error loading texture into OpenGL.");
        pResource.close();
        delete[] rowPtrs; delete[] image;
        if (pngPtr != NULL) {
            png_infop* infoPtrP = infoPtr != NULL ? &infoPtr: NULL;
            png_destroy_read_struct(&pngPtr, infoPtrP, NULL);
        }
        return NULL;
}
status GraphicsManager::update() {
    static float clearColor = 0.0f;
    clearColor += 0.001f;
    //预置清除时使用的颜色
    glClearColor(clearColor,clearColor,clearColor,1.0f);
    //用上面设置的颜色清除缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    if(eglSwapBuffers(mDisplay,mSurface) != EGL_TRUE){
        Log::error("Error %d swapping buffers.", eglGetError());
        return STATUS_KO;
    } else {
        return STATUS_OK;
    }
}
