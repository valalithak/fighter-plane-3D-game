#include "main.h"
#include "missile.h"
#include "bomb.h"
#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle {
public:
    Obstacle() {}
    Obstacle(float x, float y, float z, int index, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool tick_m(Missile m);
    bool tick_b(Bomb b);
    bool shot;
    int i;
    float rotation;
    bool volcano;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    

};

#endif 
