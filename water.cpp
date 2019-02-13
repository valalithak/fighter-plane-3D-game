#include "water.h"
#include "main.h"

Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 0.5 triangles each, so this makes 6*0.5=110 triangles, and 110*3 vertices
    static const GLfloat vertex_buffer_data[] = {

    -10000,-0.5,-10000, // triangle 1 : begin
    -10000,-0.5, 10000,
    -10000, 0.5, 10000, // triangle 1 : end

    10000, 0.5,-10000, // triangle 0.5 : begin
    -10000,-0.5,-10000,
    -10000, 0.5,-10000, // triangle 0.5 : end

    10000,-0.5, 10000,
    -10000,-0.5,-10000,
    10000,-0.5,-10000,

    10000, 0.5,-10000,
    10000,-0.5,-10000,
    -10000,-0.5,-10000,

    -10000,-0.5,-10000,
    -10000, 0.5, 10000,
    -10000, 0.5,-10000,

    10000,-0.5, 10000,
    -10000,-0.5, 10000,
    -10000,-0.5,-10000,

    -10000, 0.5, 10000,
    -10000,-0.5, 10000,
    10000,-0.5, 10000,

    10000, 0.5, 10000,
    10000,-0.5,-10000,
    10000, 0.5,-10000,

    10000,-0.5,-10000,
    10000, 0.5, 10000,
    10000,-0.5, 10000,

    10000, 0.5, 10000,
    10000, 0.5,-10000,
    -10000, 0.5,-10000,

    10000, 0.5, 10000,
    -10000, 0.5,-10000,
    -10000, 0.5, 10000,

    10000, 0.5, 10000,
    -10000, 0.5, 10000,
    10000,-0.5, 10000

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