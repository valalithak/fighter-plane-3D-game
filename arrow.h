#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {} 
    Arrow(float x, float y, float z, int index);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bool shot;
    int index;
    float rotation;
    float yaw;
private:
    VAO *object;
    VAO *object2;
    

};

#endif 
