#include "ActivityTest.h"
#include "Log.h"
#include <unistd.h>

static const int32_t SHIP_SIZE = 64;

ActivityTest::ActivityTest(android_app* pApplication):
        mGraphicsManager(pApplication),
        mEventLoop(pApplication, *this),
        mShip(pApplication,mGraphicsManager){
    Log::info("Creating ActivityTest");
    GraphicsElement * shipGraphics = mGraphicsManager.registerElement(SHIP_SIZE,SHIP_SIZE);
    mShip.registerShip(shipGraphics);
}

void ActivityTest::run() {
    mEventLoop.run();
}

status ActivityTest::onActivate() {
    Log::info("Activating ActivityTest");
    if(mGraphicsManager.start() != STATUS_OK)return STATUS_KO;

    mShip.initialize();

    return STATUS_OK;
}
void ActivityTest::onDeactivate() {
    Log::info("Deactivating ActivityTest");
}
status ActivityTest::onStep() {
    Log::info("Starting step");
    status ret = mGraphicsManager.update();
    usleep(1000000);
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
