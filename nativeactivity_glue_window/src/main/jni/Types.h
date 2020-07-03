
#ifndef FIRSTNDK_TYPES_HPP_
#define FIRSTNDK_TYPES_HPP_

#include <cstdlib>
typedef int32_t  status;
const status STATUS_OK = 0;
const status STATUS_KO = -1;
const status STATUS_EXIT = -2;

//保存绘图的坐标
struct  Location{
    Location():x(0.0f),y(0.0f){};
    float x;
    float y;
};

#define RAND(pMax) (float(pMax) * float(rand()) / float(RAND_MAX))
#endif