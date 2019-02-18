#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float radius, color_t color);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();

    bool appear;
    double speed;
    double acc_g;
    bool onground;
    float rotation;
    

private:
    VAO *object;
};

#endif