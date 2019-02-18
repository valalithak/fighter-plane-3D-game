#include "main.h"
#include "smokering.h"
#include "plane.h"


Smokering::Smokering(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[20000];
    long long int i, j;
    long long int n = 1000;

    this->radius = 5;

    float theta = 0;

    for (i = 0; i < 18 * n; i += 18) {
        vertex_buffer_data[i] = 0;
        vertex_buffer_data[i + 1] = this->radius * cos(theta);
        vertex_buffer_data[i + 2] = this->radius * sin(theta);
        
        vertex_buffer_data[i + 3] = 0;
        vertex_buffer_data[i + 4] = this->radius * cos(theta) + 0.3;
        vertex_buffer_data[i + 5] = this->radius * sin(theta);
        
        vertex_buffer_data[i + 6] = 0;
        vertex_buffer_data[i + 7] = this->radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 8] = this->radius * sin(theta + (2 * M_PI / n));
        
        vertex_buffer_data[i + 9] = 0;
        vertex_buffer_data[i + 10] = this->radius * cos(theta) + 0.3;
        vertex_buffer_data[i + 11] = this->radius * sin(theta);

        vertex_buffer_data[i + 12] = 0;
        vertex_buffer_data[i + 13] = this->radius * cos(theta + (2 * M_PI / n)) + 0.3;
        vertex_buffer_data[i + 14] = this->radius * sin(theta + (2 * M_PI / n)) + 0.3;

        vertex_buffer_data[i + 15] = 0;
        vertex_buffer_data[i + 16] = this->radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 17] = this->radius * sin(theta + (2 * M_PI / n));

        theta += (2 * M_PI) / n;
    }

    this->object = create3DObject(GL_TRIANGLES, 6 * n, vertex_buffer_data, color, GL_FILL);
    

}

void Smokering::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bool Smokering::isPlane(Plane plane) {
    float dist = (this->position.x - plane.position.x) * (this->position.x - plane.position.x);
    dist += (this->position.y - plane.position.y) * (this->position.y - plane.position.y);
    dist += (this->position.z - plane.position.z) * (this->position.z - plane.position.z);

    if (dist <= this->radius * this->radius) {
        if ((plane.position.x - 2 < this->position.x && plane.position.x + 2 > this->position.x) || (plane.position.x - 2 > this->position.x && plane.position.x + 2 < this->position.x)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}