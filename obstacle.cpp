#include "obstacle.h"
#include "main.h"
#include "missile.h"
#include "bomb.h"
Obstacle::Obstacle(float x, float y, float z, int index, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->shot = false;
    this->rotation = 90;
    this->i = index;
    if (index % 10 == 0)
        this->volcano = true;
    else
        this->volcano = false;

    GLfloat b = 3; // basesize = 2b
    GLfloat h = 2; // basesize = 2b

    // For 2-d Top view at z = 0
    static const GLfloat base[] = {
        b,
        0.0f,
        b,
        -b,
        0.0f,
        b,
        -b,
        0.0f,
        -b,

        -b,
        0.0f,
        -b,
        b,
        0.0f,
        -b,
        b,
        0.0f,
        b,
    };

    static const GLfloat pyramid[] = {
        // front
        b,
        0.0f,
        b,
        -b,
        0.0f,
        b,
        0.0f,
        h,
        0.0f,

        // back
        b,
        0.0f,
        -b,
        -b,
        0.0f,
        -b,
        0.0f,
        h,
        0.0f,

        //left
        -b,
        0.0f,
        b,
        -b,
        0.0f,
        -b,
        0.0f,
        h,
        0.0f,

        //right
        b,
        0.0f,
        b,
        b,
        0.0f,
        -b,
        0.0f,
        h,
        0.0f,

    };



    this->object = create3DObject(GL_TRIANGLES, 6, base, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 24, pyramid, color, GL_FILL);
    
}

void Obstacle::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
   
}
void Obstacle::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

bool Obstacle::tick_m(Missile m)
{
    if (m.shot)
    {
        float distx = (this->position.x - m.position.x) * (this->position.x - m.position.x);
        float disty = (this->position.y - m.position.y) * (this->position.y - m.position.y);
        float distz = (this->position.z - m.position.z) * (this->position.z - m.position.z);
        float box = 1;
        if (distx <= box)
            return true;
        else

            return false;
    }
}
bool Obstacle::tick_b(Bomb b)
{
    if (b.appear)
    {
        float distx = (this->position.x - b.position.x) * (this->position.x - b.position.x);
        float disty = (this->position.y - b.position.y) * (this->position.y - b.position.y);
        float distz = (-this->position.z + b.position.z) * (this->position.z - b.position.z);
        float box = 1;
        if (distx <= box && distz <= box)
            return true;
        else
            return false;
    }
}
