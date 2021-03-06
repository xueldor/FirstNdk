#include "ActivityTest.h"
#include "Log.h"
#include <unistd.h>

static const int32_t SHIP_SIZE = 64;
static const int32_t SQUARE_COUNT = 16;
static const int32_t SQUARE_SIZE = 64;

ActivityTest::ActivityTest(android_app* pApplication):
        mTimeManager(),
        mPhysicsManager(mTimeManager,mGraphicsManager),
        mGraphicsManager(pApplication),
        mEventLoop(pApplication, *this),
        mAsteroidTexture(pApplication, "maps.png"),
        mShipTexture(pApplication, "novelty.png"){
    Log::info("Creating ActivityTest");
}

void ActivityTest::run() {
    mEventLoop.run();
}

status ActivityTest::onActivate() {
    Log::info("Activating ActivityTest");
    if(mGraphicsManager.start() != STATUS_OK)return STATUS_KO;
    mGraphicsManager.loadTexture(mAsteroidTexture);
    mGraphicsManager.loadTexture(mShipTexture);
    mTimeManager.reset();
    return STATUS_OK;
}
void ActivityTest::onDeactivate() {
    Log::info("Deactivating ActivityTest");
}
status ActivityTest::onStep() {
    Log::info("Starting step");
    mTimeManager.update();
    mPhysicsManager.update();
    status ret = mGraphicsManager.update();
    Log::info("Stepping done");
    return ret;
}
void ActivityTest::onStart() {
    Log::info("onStart");
}
void ActivityTest::onResume() {
    Log::info("onResume");
}
void ActivityTest::onPause() {
    Log::info("onPause");
}
void ActivityTest::onStop() {
    Log::info("onStop");
}
void ActivityTest::onDestroy() {
    Log::info("onDestroy");
}
void ActivityTest::onSaveInstanceState(void** pData, size_t* pSize) {
    Log::info("onSaveInstanceState");
}
void ActivityTest::onConfigurationChanged() {
    Log::info("onConfigurationChanged");
}
void ActivityTest::onLowMemory() {
    Log::info("onLowMemory");
}
void ActivityTest::onCreateWindow() {
    Log::info("onCreateWindow");
}
void ActivityTest::onDestroyWindow() {
    Log::info("onDestroyWindow");
}
void ActivityTest::onGainFocus() {
    Log::info("onGainFocus");
}
void ActivityTest::onLostFocus() {
    Log::info("onLostFocus");
}
