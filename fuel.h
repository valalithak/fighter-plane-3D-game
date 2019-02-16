#include "main.h"

#ifndef FUEL_H
#define FUEL_H


class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z, float ind, color_t color1, color_t color2);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float rotation;
    float f;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif 
