#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color, color_t color2);
    glm::vec3 position;
    float rotation;
    float roll;
    float pitch;
    float yaw;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    double acc_g;
    double health;
    bool gravity;
    bool loopback;
    float lives;
private:
    VAO *object0;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
    VAO *object10;
    VAO *object11;
    VAO *object12;
    VAO *object13;
    VAO *walla;
    VAO *wallb;
    VAO *wallc;
    VAO *walld;
    VAO *walle;
    VAO *wallf;
    VAO *wallg;
    VAO *wallh;
    VAO *walli;
    VAO *wallj;
    VAO *wallk;

};

#endif // PLANE_H
