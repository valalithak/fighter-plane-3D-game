#include "water.h"
#include "main.h"

Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 0.5 triangles each, so this makes 6*0.5=110 triangles, and 110*3 vertices
    GLfloat w = 10000;
    GLfloat zn = -10.0f;
    GLfloat zf = -10000.0f;
    static const GLfloat vertex_buffer_data[] = {
        // top
        -w, -w, zn,
         w, -w, zn,
         w, w, zn,

         -w, -w, zn,
         -w, w, zn, 
         w, w, zn,
        // bottom
          -w, -w, zf,
         w, -w, zf,
         w, w, zf,

         -w, -w, zf,
         -w, w, zf, 
         w, w, zf,

         // left
         -w, w, zn,
         -w, w, zf,
         -w, -w, zn,

         -w, -w, zn
         -w, -w, zf,
         -w, w, zf, 

         // right
         w, w, zn,
         w, w, zf,
         w, -w, zn,

         w, -w, zn,
         w, -w, zf,
         w, w, zf, 




    
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Water::tick() {
      this->rotation += speed;
}