#include "main.h"
#include "parachute.h"
#include "missile.h"
Parachute::Parachute(float x, float y, float z, int index) {
    this->position = glm::vec3(x, y, z);
    this->index = index;
    long long int n = 1000;
    this->shot = false;
    GLfloat para[100000];
    float theta = 0;

    long long int i;
    this->height = 3;
    this-> R = 1;
    this->r = 3;

    for (i = 0; i < 18 * n; i += 18) {
        para[i] = this->r * cos(theta);
        para[i + 1] = 0;
        para[i + 2] = this->r * sin(theta);

        para[i + 3] = this->r * cos(theta + (2 * M_PI / n));
        para[i + 4] = 0;
        para[i + 5] = this->r * sin(theta + +(2 * M_PI / n));

        para[i + 6] = this->R * cos(theta);
        para[i + 7] = this->height;
        para[i + 8] = this->R * sin(theta);

        para[i + 9] = this->r * cos(theta + (2 * M_PI / n));
        para[i + 10] = 0;
        para[i + 11] = this->r * sin(theta + (2 * M_PI / n));

        para[i + 12] = this->R * cos(theta + (2 * M_PI / n));
        para[i + 13] = this->height;
        para[i + 14] = this->R * sin(theta + +(2 * M_PI / n));

        para[i + 15] = this->R * cos(theta);
        para[i + 16] = this->height;
        para[i + 17] = this->R * sin(theta);

        theta += (2 * M_PI) / n;
    }

    this->object = create3DObject(GL_TRIANGLES, 6 * n, para, COLOR_DARKBLUE, GL_FILL);
    

}

void Parachute::draw(glm::mat4 VP) {
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
int count  = 20;
int flag = 0;
void Parachute::tick()
{
     
    if(flag == 0)
    {
        this->position.z -= 0.01;
        count --;
        if(count == 0)
        {
            flag = 1;
            count  = 20;
        }
    }
    if(flag == 1)
    {
        this->position.z += 0.01;
        count --;
        if(count == 0)
        {
            flag = 0;
            count  = 20;
        }
    }
}

bool Parachute::isShot(Missile m)
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

