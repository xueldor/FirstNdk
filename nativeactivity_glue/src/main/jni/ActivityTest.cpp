#include "ActivityTest.h"
#include "Log.h"
#include <unistd.h>


ActivityTest::ActivityTest(android_app* pApplication): mEventLoop(pApplication, *this) {
    Log::info("Creating ActivityTest");
}

void ActivityTest::run() {
    mEventLoop.run();
}

status ActivityTest::onActivate() {
    Log::info("Activating ActivityTest");
    return STATUS_OK;
}
void ActivityTest::onDeactivate() {
    Log::info("Deactivating ActivityTest");
}
status ActivityTest::onStep() {
    Log::info("Starting step");
    usleep(300000);
    Log::info("Stepping done");
    return STATUS_OK;
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
