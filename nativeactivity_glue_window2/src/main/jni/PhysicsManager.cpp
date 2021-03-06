#include "PhysicsManager.h"
#include "Log.h"

PhysicsManager::PhysicsManager(TimeManager& pTimeManager,GraphicsManager& pGraphicsManager) :
        mTimeManager(pTimeManager), mGraphicsManager(pGraphicsManager),mPhysicsBodies(), mPhysicsBodyCount(0){
    Log::info("Creating PhysicsManager.");
}

PhysicsManager::~PhysicsManager() {
    Log::info("Destroying PhysicsManager.");
    for (int32_t i = 0; i < mPhysicsBodyCount; ++i) {
        delete mPhysicsBodies[i];
    }
}

PhysicsBody* PhysicsManager::loadBody(Location& pLocation,int32_t pSizeX, int32_t pSizeY) {
    PhysicsBody* body = new PhysicsBody(&pLocation,pSizeX,pSizeY);
    mPhysicsBodies[mPhysicsBodyCount++] = body;
    return body;
}

void PhysicsManager::update() {
    float timeStep = mTimeManager.elapsed();
    for (int32_t i = 0; i < mPhysicsBodyCount; ++i) {
        PhysicsBody* body = mPhysicsBodies[i];
        body->location->x += (timeStep * body->velocityX);//间隔*速率 计算出偏移
        body->location->y += (timeStep * body->velocityY);
    }
}