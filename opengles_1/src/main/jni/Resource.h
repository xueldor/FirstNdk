#ifndef FIRSTNDK_RESOURCE_H
#define FIRSTNDK_RESOURCE_H

#include "Types.h"
#include <android_native_app_glue.h>

class Resource {
public:
    Resource(android_app* pApplication, const char* pPath);

    const char* getPath(){ return mPath;};

    status open();
    void close();
    status read(void* pBuffer,size_t pCount);
    bool operator==(const Resource& pOther);

private:
    const char* mPath;
    AAssetManager* mAssetManager;
    AAsset* mAsset;
};


#endif //FIRSTNDK_RESOURCE_H
