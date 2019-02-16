#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x_coord, float y_coord, float z_coord, int val, color_t color);
    glm::vec3 position;
    float val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();




private:

    VAO *object0;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif
