#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float rad, color_t color);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();

    bool appear;
    double speed;
    double acc_g;
    bool onground;
    

private:
    VAO *object;
};

#endif