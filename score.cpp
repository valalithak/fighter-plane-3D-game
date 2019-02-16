#include "score.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Score::Score(float x_coord, float y_coord, float z_coord, int val, color_t color)
{
    this->val = val;
    float y = 2*0.3;
    float x= 2*0.05;
    float d = 2*0.15;
    this->position = glm::vec3(x_coord, y_coord, 0);
    GLfloat vertex_buffer_data[7][18] = {

        //vertex_buffer_data[0] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, y, 0.0f,
            x, 0.0f, 0.0f,
            x, 0.0f, 0.0f,
            0.0f, y, 0.0f,
            x, y, 0.0f,

        },
        //vertex_buffer_data[1] =
        {
            0.0f, y, 0.0f,
            0.0f, y+x, 0.0f,
            d+x, y, 0.0f,
            d+x, y, 0.0f,
            d+x, y+x, 0.0f,
            0.0f, y+x, 0.0f,


        },
        //vertex_buffer_data[2] =
        {
            d, 0.0f, 0.0f,
            d, y, 0.0f,
            x+d, 0.0f, 0.0f,
            x+d, 0.0f, 0.0f,
            d, y, 0.0f,
            x+d, y, 0.0f,
        },
        //vertex_buffer_data[3] =
        {
            d, 0.0f, 0.0f,
            d, -y, 0.0f,
            x+d, 0.0f, 0.0f,
            d, -y, 0.0f,
            x+d, -y, 0.0f,
            x+d, 0.0f, 0.0f,
        },
        //vertex_buffer_data[4] =
        {
            0.0f, -y, 0.0f,
            0.0f, -(y+x), 0.0f,
            d+x, -y, 0.0f,
            d+x, -y, 0.0f,
            d+x, -(y+x), 0.0f,
            0.0f, -(y+x), 0.0f,

        },
        //vertex_buffer_data[5] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, -y, 0.0f,
            x, 0.0f, 0.0f,
            x, 0.0f, 0.0f,
            0.0f, -y, 0.0f,
            x, -y, 0.0f,


        },
        //vertex_buffer_data[6] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, x, 0.0f,
            d, 0.0f, 0.0f,
            d, 0.0f, 0.0f,
            d, x, 0.0f,
            0.0f, x, 0.0f,
        }
    };
        this->object0 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[0], color, GL_FILL);
        this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[1], color, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[2], color, GL_FILL);
        this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[3], color, GL_FILL);
        this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[4], color, GL_FILL);
        this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[5], color, GL_FILL);
        this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data[6], color, GL_FILL);
}

void Score::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->val == 0){
        draw3DObject(this->object0);
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
        draw3DObject(this->object4);
        draw3DObject(this->object5);
    }
    if(this->val == 1){
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if(this->val == 2){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object5);
        draw3DObject(this->object4);
        draw3DObject(this->object6);
    }
    if(this->val == 3){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object6);
        draw3DObject(this->object3);
        draw3DObject(this->object4);
    }
    if(this->val == 4){
        draw3DObject(this->object0);
        draw3DObject(this->object6);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }

    if(this->val == 5){
        draw3DObject(this->object0);
        draw3DObject(this->object1);
        draw3DObject(this->object3);
        draw3DObject(this->object4);
        draw3DObject(this->object6);
    }
    if(this->val == 6)
    {
        draw3DObject(this->object0);
        draw3DObject(this->object1);
        draw3DObject(this->object3);
        draw3DObject(this->object5);
        draw3DObject(this->object4);
        draw3DObject(this->object6);
    }
    if(this->val == 7){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if(this->val == 8){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
        draw3DObject(this->object4);
        draw3DObject(this->object6);
        draw3DObject(this->object5);
        draw3DObject(this->object0);
    }
    if(this->val == 9){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
        draw3DObject(this->object6);
        draw3DObject(this->object0);
    }



}
