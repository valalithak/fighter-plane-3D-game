#include "main.h"
#include "plane.h"

#ifndef SMOKERING_H
#define SMOKERING_H

class Smokering {
    public:
        Smokering() {}
        Smokering (float x, float y, float z, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        float radius;
        bool collided;
        float gr;
        bool isPlane(Plane plane);
    private:
        VAO *object;
};

#endif