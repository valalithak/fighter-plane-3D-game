#include "obstacle.h"
#include "main.h"

Obstacle::Obstacle(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->shot = false;
    this->rotation  = 0;

    GLfloat b = 0.5; // basesize = 2b
    GLfloat h = 0.7; // basesize = 2b

    // For 2-d Top view at z = 0
    static const GLfloat base[] = {
        b, 0.0f, b,
        -b, 0.0f,b,
        -b,0.0f, -b, 

        -b, 0.0f, -b, 
        b, 0.0f, -b, 
        b, 0.0f, b, 
    };
    
    static const GLfloat pyramid[] = {
         // front
         b, 0.0f, b,
         -b, 0.0f, b,
         0.0f, h, 0.0f,

         // back
          b, 0.0f, -b,
         -b, 0.0f, -b,
         0.0f, h, 0.0f,

         //left
         -b, 0.0f, b,
         -b, 0.0f, -b,
         0.0f, h, 0.0f,

         //right 
         b, 0.0f, b,
         b, 0.0f, -b,
         0.0f, h, 0.0f,


    };
   

    this->object = create3DObject(GL_TRIANGLES, 6, base, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 24, pyramid, color, GL_FILL);
}

void Obstacle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
   // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
   //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
   Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}
void Obstacle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Obstacle::tick() {

}

