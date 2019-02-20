#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z, int index) {
   this->position = glm::vec3(x, y, z);

    long long int n = 1000;
    long long int i, j;
    GLfloat arrow[200000];
    float r = 0.5;
    this->rotation = 90;
    this->yaw = 270;

    float theta = 0;

    for (i = 0; i < 9 * n; i += 9)
    {
        arrow[i] = 1;
        arrow[i + 1] = r * sin(theta);
        arrow[i + 2] = r * cos(theta);
        arrow[i + 3] = 2;
        arrow[i + 4] = 0;
        arrow[i + 5] = 0;
        arrow[i + 6] = 1;
        arrow[i + 7] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 8] = r * cos(theta + (2 * 3.14159) / n);

        theta += ((2 * 3.14159) / n);
    }

    theta = 0;

    for(i = 9 * n; i < 27 * n; i += 18)
    {
        arrow[i] = 0;
        arrow[i + 1] = r * sin(theta);
        arrow[i + 2] = r * cos(theta);

        arrow[i + 3] = 1;
        arrow[i + 4] = r * sin(theta);
        arrow[i + 5] = r * cos(theta);

        arrow[i + 6] = 0;
        arrow[i + 7] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 8] = r * cos(theta + (2 * 3.14159) / n);

        arrow[i + 9] = 0;
        arrow[i + 10] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 11] = r * cos(theta + (2 * 3.14159) / n);

        arrow[i + 12] = 1;
        arrow[i + 13] = r * sin(theta);
        arrow[i + 14] = r * cos(theta);

        arrow[i + 15] = 1;
        arrow[i + 16] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 17] = r * cos(theta + (2 * 3.14159) / n);

        theta += ((2 * 3.14159) / n);
    }

    theta = 0;

    for (i = 27 * n; i < 45 * n; i += 18)
    {
        arrow[i] = 0;
        arrow[i + 1] = r * sin(theta);
        arrow[i + 2] = r * cos(theta);

        arrow[i + 3] = -1;
        arrow[i + 4] = r * sin(theta);
        arrow[i + 5] = r * cos(theta);

        arrow[i + 6] = 0;
        arrow[i + 7] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 8] = r * cos(theta + (2 * 3.14159) / n);

        arrow[i + 9] = 0;
        arrow[i + 10] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 11] = r * cos(theta + (2 * 3.14159) / n);

        arrow[i + 12] = -1;
        arrow[i + 13] = r * sin(theta);
        arrow[i + 14] = r * cos(theta);

        arrow[i + 15] = -1;
        arrow[i + 16] = r * sin(theta + (2 * 3.14159) / n);
        arrow[i + 17] = r * cos(theta + (2 * 3.14159) / n);

        theta += ((2 * 3.14159) / n);
    }
    
    

    this->object = create3DObject(GL_TRIANGLES, 15 * n + 3, arrow, COLOR_RED, GL_FILL);
} 

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * 3.14159 / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate2    = glm::rotate((float) ((this->yaw)* 3.14159 / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate3    = glm::rotate((float) (180* 3.14159 / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
   //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // printf("here %f\n",this->rotation);
      
    Matrices.model *= (translate*rotate3*rotate*rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {

}

