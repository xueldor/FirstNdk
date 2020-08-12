#ifndef FIRSTNDK_SQUARE_H
#define FIRSTNDK_SQUARE_H

#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "TimeManager.h"
#include "Types.h"

class Square {
public:
    Square(android_app* pApplication,TimeManager& pTimeManager,GraphicsManager& pGraphicsManager,PhysicsManager& pPhysicsManager);
    void registerSquare(Location& pLocation,int32_t pSizeX,int32_t pSizeY);
    void initialize();
    void update();

private:
    void spawn(PhysicsBody* pBody);

    TimeManager& mTimeManager;
    GraphicsManager& mGraphicsManager;
    PhysicsManager& mPhysicsManager;

    PhysicsBody* mBodies[1024];int32_t mBodyCount;
    float mMinBound;
    float mUpperBound; float mLowerBound;
    float mLeftBound; float mRightBound;

};


#endif //FIRSTNDK_SQUARE_H
