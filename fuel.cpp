#include "fuel.h"
#include "main.h"

Fuel::Fuel(float x, float y, float z, float ind, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, z);
    this->f = ind; 
    
    this->rotation  = 0;

   GLfloat l = 4; // total length of bar
   GLfloat h = 0.5; // height of bar


    // For 2-d Top view at z = 0
    GLfloat green_full[] = {
         0.0f, 0.0f, 0.0f, 
         l, 0.0f, 0.0f,
         0.0f, h, 0.0f,

         0.0f, h, 0.0f,
         l, h, 0.0f, 
         l, 0.0f, 0.0f,

    };

     GLfloat green_half[] = {
         0.0f, 0.0f, 0.0f, 
         l/2, 0.0f, 0.0f,
         0.0f, h, 0.0f,

         0.0f, h, 0.0f,
         l/2, h, 0.0f, 
         l/2, 0.0f, 0.0f,

    };

    
    GLfloat red[] = {
         0.0f, 0.0f, 0.0f, 
         l/4, 0.0f, 0.0f,
         0.0f, h, 0.0f,

         0.0f, h, 0.0f,
         l/4, h, 0.0f, 
         l/4, 0.0f, 0.0f,

       
    };
   

    this->object = create3DObject(GL_TRIANGLES, 6, green_full, color1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, green_half, color1, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, red, color2, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
   // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
   //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
   Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->f > 750)
        draw3DObject(this->object);
    else if(this->f > 100)
        draw3DObject(this->object2);
    else 
        draw3DObject(this->object3);
    

}
void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

