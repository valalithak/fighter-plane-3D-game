#include "main.h"
#include "missile.h"
#include "plane.h"

Missile::Missile(float x, float y, float z, float radius, color_t color) {
    this->position = glm::vec3(x, y, z);

    long long int n = 1000;
    long long int i, j;
    GLfloat bullet[200000];
    float r = radius; // 0.1;
    this->rotation = 90;
    this->shot = false;
    this->yaw = 0;

    float theta = 0;

    for (i = 0; i < 9 * n; i += 9)
    {
        bullet[i] = 1;
        bullet[i + 1] = r * sin(theta);
        bullet[i + 2] = r * cos(theta);
        bullet[i + 3] = 2;
        bullet[i + 4] = 0;
        bullet[i + 5] = 0;
        bullet[i + 6] = 1;
        bullet[i + 7] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 8] = r * cos(theta + (2 * 3.14159) / n);

        theta += ((2 * 3.14159) / n);
    }

    theta = 0;

    for(i = 9 * n; i < 27 * n; i += 18)
    {
        bullet[i] = 0;
        bullet[i + 1] = r * sin(theta);
        bullet[i + 2] = r * cos(theta);

        bullet[i + 3] = 1;
        bullet[i + 4] = r * sin(theta);
        bullet[i + 5] = r * cos(theta);

        bullet[i + 6] = 0;
        bullet[i + 7] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 8] = r * cos(theta + (2 * 3.14159) / n);

        bullet[i + 9] = 0;
        bullet[i + 10] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 11] = r * cos(theta + (2 * 3.14159) / n);

        bullet[i + 12] = 1;
        bullet[i + 13] = r * sin(theta);
        bullet[i + 14] = r * cos(theta);

        bullet[i + 15] = 1;
        bullet[i + 16] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 17] = r * cos(theta + (2 * 3.14159) / n);

        theta += ((2 * 3.14159) / n);
    }

    theta = 0;

    for (i = 27 * n; i < 45 * n; i += 18)
    {
        bullet[i] = 0;
        bullet[i + 1] = r * sin(theta);
        bullet[i + 2] = r * cos(theta);

        bullet[i + 3] = -1;
        bullet[i + 4] = r * sin(theta);
        bullet[i + 5] = r * cos(theta);

        bullet[i + 6] = 0;
        bullet[i + 7] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 8] = r * cos(theta + (2 * 3.14159) / n);

        bullet[i + 9] = 0;
        bullet[i + 10] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 11] = r * cos(theta + (2 * 3.14159) / n);

        bullet[i + 12] = -1;
        bullet[i + 13] = r * sin(theta);
        bullet[i + 14] = r * cos(theta);

        bullet[i + 15] = -1;
        bullet[i + 16] = r * sin(theta + (2 * 3.14159) / n);
        bullet[i + 17] = r * cos(theta + (2 * 3.14159) / n);

        theta += ((2 * 3.14159) / n);
    }
    
    

    this->object = create3DObject(GL_TRIANGLES, 15 * n + 3, bullet, color, GL_FILL);
} 

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * 3.14159 / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2    = glm::rotate((float) ((this->yaw)* 3.14159 / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate3    = glm::rotate((float) (90* 3.14159 / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
   //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
  
      
    Matrices.model *= (translate*rotate3*rotate*rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::tick(Plane plane) {

    int count = 250;
    this->yaw = plane.yaw;


    if(count > 0)
    {
        float a = (plane.yaw * 3.14) / 180;
        this->position.y += 0.5 * cos(a);
        this->position.x -= 0.5 * sin(a);
        count --;
    }
    if(count == 0)
        this->shot = false;
    //this->position += this->speed;
}