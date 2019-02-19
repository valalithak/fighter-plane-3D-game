#include "main.h"
#include "plane.h"
#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool tick_plane(Plane plane);
    double speed;
    bool taken;
private:
    VAO *object;
};

#endif // BALL_H
