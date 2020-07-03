#include "Ship.h"
#include "Log.h"
#include "Types.h"

static const float INITAL_X = 0.5f;
static const float INITAL_Y = 0.25f;

Ship::Ship(android_app *pApplication, GraphicsManager &pGraphicsManager):
        mGraphicsManager(pGraphicsManager),mGraphics(NULL) {

}
void Ship::registerShip(GraphicsElement* pGraphics) {
    mGraphics = pGraphics;
}
void Ship::initialize() {
    //设置location 横坐标为屏幕中间
    mGraphics->location.x = INITAL_X * mGraphicsManager.getRenderWidth();
    //设置location 纵坐标为屏幕下方四分之一处
    mGraphics->location.y = INITAL_Y * mGraphicsManager.getRenderHeight();
}