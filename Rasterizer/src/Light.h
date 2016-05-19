#pragma once

#include "Vector3.h"
#include "Color.h"

//Which is actually a directional light
class Light
{
public:
    Light() {};
    ~Light() {};
    
    Vector3 direction;
    //Vector3 position;
    Color color;
    float itensity;
private:
    
};