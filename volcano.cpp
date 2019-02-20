#include "main.h"
#include "volcano.h"
#include "missile.h"
Volcano::Volcano(float x, float y, float z, int index) {
    this->position = glm::vec3(x, y, z);
    this->index = index;
    long long int n = 1000;
    this->shot = false;
    GLfloat volc[100000];
    float theta = 0;

    long long int i;
    this->height = 1;
    this-> R = 0.5;
    this->r = 4;

    for (i = 0; i < 18 * n; i += 18) {
        volc[i] = this->r * cos(theta);
        volc[i + 1] = 0;
        volc[i + 2] = this->r * sin(theta);

        volc[i + 3] = this->r * cos(theta + (2 * M_PI / n));
        volc[i + 4] = 0;
        volc[i + 5] = this->r * sin(theta + +(2 * M_PI / n));

        volc[i + 6] = this->R * cos(theta);
        volc[i + 7] = this->height;
        volc[i + 8] = this->R * sin(theta);

        volc[i + 9] = this->r * cos(theta + (2 * M_PI / n));
        volc[i + 10] = 0;
        volc[i + 11] = this->r * sin(theta + (2 * M_PI / n));

        volc[i + 12] = this->R * cos(theta + (2 * M_PI / n));
        volc[i + 13] = this->height;
        volc[i + 14] = this->R * sin(theta + +(2 * M_PI / n));

        volc[i + 15] = this->R * cos(theta);
        volc[i + 16] = this->height;
        volc[i + 17] = this->R * sin(theta);

        theta += (2 * M_PI) / n;
    }

    this->object = create3DObject(GL_TRIANGLES, 6 * n, volc, COLOR_BLACK, GL_FILL);
    

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
   
}

bool Volcano::isShot(Missile m)
{
    if (m.shot)
    {
        float distx = (this->position.x - m.position.x) * (this->position.x - m.position.x);
        float disty = (this->position.y - m.position.y) * (this->position.y - m.position.y);
        float distz = (this->position.z - m.position.z) * (this->position.z - m.position.z);
        float box = 1;
        if (distx <= box && disty <= box)
            return true;
        else

            return false;
    }
}

