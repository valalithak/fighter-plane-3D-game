#include "main.h"
#include "missile.h"

Missile::Missile(float x, float y, float z, float radius, color_t color) {
    this->position = glm::vec3(x, y, z);

    long long int n = 1000;
    long long int i, j;
    GLfloat coord[200000];
    float r = radius; // 0.1;
    this->rotation = 0;
    

    float theta = 0;

    for (i = 0; i < 9 * n; i += 9)
    {
        coord[i] = 2;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);
        coord[i + 3] = 3;
        coord[i + 4] = 0;
        coord[i + 5] = 0;
        coord[i + 6] = 2;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for(i = 9 * n; i < 27 * n; i += 18)
    {
        coord[i] = 0;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);

        coord[i + 3] = 2;
        coord[i + 4] = r * sin(theta);
        coord[i + 5] = r * cos(theta);

        coord[i + 6] = 0;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 9] = 0;
        coord[i + 10] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 11] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 12] = 2;
        coord[i + 13] = r * sin(theta);
        coord[i + 14] = r * cos(theta);

        coord[i + 15] = 2;
        coord[i + 16] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for (i = 27 * n; i < 45 * n; i += 18)
    {
        coord[i] = 0;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);

        coord[i + 3] = -2;
        coord[i + 4] = r * sin(theta);
        coord[i + 5] = r * cos(theta);

        coord[i + 6] = 0;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 9] = 0;
        coord[i + 10] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 11] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 12] = -2;
        coord[i + 13] = r * sin(theta);
        coord[i + 14] = r * cos(theta);

        coord[i + 15] = -2;
        coord[i + 16] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }
    
    GLfloat coord_fin[] = {
        -2.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -2.0f, 2.0f, 0.0f,
    };

    GLfloat coord_wing[] = {
        -0.25f, 0.0f, 1.0f,
        0.75f, 0.0f, 1.0f,
        -0.25f, 0.0f, 3.0f,
        -0.25f, 0.0f, -1.0f,
        0.75f, 0.0f, -1.0f,
        -0.25f, 0.0f, -3.0f,
        -2.0f, 0.0f, 1.0f,
        -2.0f, 0.0f, 1.5f,
        -1.5f, 0.0f, 1.0f,
        -2.0f, 0.0f, -1.0f,
        -2.0f, 0.0f, -1.5f,
        -1.5f, 0.0f, -1.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 15 * n + 3, coord, color, GL_FILL);
} 

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
       // glTranslatef
      
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::tick() {
    //this->position += this->speed;
}