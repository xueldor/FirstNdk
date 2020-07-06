#ifndef FIRSTNDK_SHIP_H
#define FIRSTNDK_SHIP_H

#include "GraphicsManager.h"

class Ship {
public:
    Ship(android_app* pApplication,GraphicsManager& pGraphicsManager);
    void registerShip(GraphicsElement* pGraphics);
    void initialize();

private:
    GraphicsManager& mGraphicsManager;
    GraphicsElement* mGraphics;
};


#endif //FIRSTNDK_SHIP_H
