#include "plane.h"
#include "score.h"
#include "main.h"

Plane::Plane(float x, float y, float z, color_t color, color_t color2) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->roll = 0;
    this->pitch = 0;
    this->yaw = 0;
    this->speed = 5;
    this->acc_g = 0.1f;
    this->health = 100;
    this->gravity = false;

    // For 2-d Top view at z = 0
    static const GLfloat buffer_0[] = {
        0.5f, 2.0f, 0.0f,
        -0.5f, 2.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
    };
    static const GLfloat buffer_1[] = {
        0.5f, 2.0f, 0.0f,
        -0.5f, -2.0f, 0.0f,
        0.5f, -2.0f, 0.0f,

        -0.5f, -2.0f, 0.0f,
        -0.5f, 2.0f, 0.0f,
        0.5f, 2.0f, 0.0f,
    };
    static const GLfloat buffer_2[] = {
       -3.0f, 0.0f, 0.0f, 
       -0.5f, 0.0f, 0.0f, 
       -0.5f, 1.0f, 0.0f,
    };
    static const GLfloat buffer_3[] = {
       3.0f, 0.0f, 0.0f, 
       0.5f, 0.0f, 0.0f, 
       0.5f, 1.0f, 0.0f,
    };
    static const GLfloat buffer_4[] = {
       -2.0f, -3.0f, 0.0f,
        0.0f, -3.0f, 0.0f,
        -0.5, -2.0f, 0.0f,
    };
    static const GLfloat buffer_5[] = {
       -0.5f, -2.0f, 0.0f,
       0.5f, -2.0f, 0.0f, 
       0.0f, -3.0f, 0.0f,
    };
    static const GLfloat buffer_6[] = {
       2.0f, -3.0f, 0.0f,
       0.0f, -3.0f, 0.0f,
       0.5, -2.0f, 0.0f,
    }; // end at z = 0

    // For bottom surface at z = d;
    GLfloat d = -0.3f;
    static const GLfloat buffer_7[] = {
        0.5f, 2.0f, d,
        -0.5f, 2.0f, d,
        0.0f, 3.0f, d,
    };
    static const GLfloat buffer_8[] = {
        0.5f, 2.0f, d,
        -0.5f, -2.0f, d,
        0.5f, -2.0f, d,

        -0.5f, -2.0f, d,
        -0.5f, 2.0f, d,
        0.5f, 2.0f, d,
    };
    static const GLfloat buffer_9[] = {
       -3.0f, 0.0f, d, 
       -0.5f, 0.0f, d, 
       -0.5f, 1.0f, d,
    };
    static const GLfloat buffer_10[] = {
       3.0f, 0.0f, d, 
       0.5f, 0.0f, d, 
       0.5f, 1.0f, d,
    };
    static const GLfloat buffer_11[] = {
       -2.0f, -3.0f, d,
        0.0f, -3.0f, d,
        -0.5, -2.0f, d,
    };
    static const GLfloat buffer_12[] = {
       -0.5f, -2.0f, d,
       0.5f, -2.0f, d, 
       0.0f, -3.0f, d,
    };
    static const GLfloat buffer_13[] = {
       2.0f, -3.0f, d,
       0.0f, -3.0f, d,
       0.5, -2.0f, d,
    };

    // walls to join two z layers

    static const GLfloat wall_a[] = {
       0.0f, 3.0f, 0.0f, 
       0.5f, 2.0f, 0.0f, 
       0.5f, 2.0f, d,

       0.0f, 3.0f, d,
       0.0f, 3.0f, 0,
       0.5f, 2.0f, d,

    };
    static const GLfloat wall_b[] = {
       0.0f, 3.0f, 0.0f, 
       -0.5f, 2.0f, 0.0f, 
       -0.5f, 2.0f, d,

       0.0f, 3.0f, d,
       0.0f, 3.0f, 0,
       -0.5f, 2.0f, d,

    };
    static const GLfloat wall_c[] = {
       -0.5f, 1.0f, 0.0f, 
       -3.0f, 0.0f, 0.0f, 
       -3.0f, 0.0f, d, 

       -0.5f, 1.0f, d, 
        -0.5f, 1.0f, 0.0f, 
       -3.0f, 0.0f, d, 

    };
    static const GLfloat wall_d[] = {
       0.5f, 1.0f, 0.0f, 
       3.0f, 0.0f, 0.0f, 
       3.0f, 0.0f, d, 

       0.5f, 1.0f, d, 
       0.5f, 1.0f, 0.0f, 
       3.0f, 0.0f, d, 

    };
    static const GLfloat wall_e[] = {
       0.5f, 0.0f, 0.0f, 
       3.0f, 0.0f, 0.0f, 
       3.0f, 0.0f, d, 

       0.5f, 0.0f, d, 
       0.5f, 0.0f, 0.0f, 
       3.0f, 0.0f, d, 

    };
    static const GLfloat wall_f[] = {
       -0.5f, 0.0f, 0.0f, 
       -3.0f, 0.0f, 0.0f, 
       -3.0f, 0.0f, d, 

       -0.5f, 0.0f, d, 
       -0.5f, 0.0f, 0.0f, 
       -3.0f, 0.0f, d, 

    };
    static const GLfloat wall_g[] = {
       -0.5f, 0.0f, 0.0f,
       -0.5f, -2.0f, 0.0f, 
       -0.5f, 0.0f, d,

       -0.5f, 0.0f, d,
       -0.5f, -2.0f, d, 
       -0.5f, -2.0f, 0.0f, 

    };
    static const GLfloat wall_h[] = {
       -0.5f, 0.0f, 0.0f,
       -0.5f, -2.0f, 0.0f, 
       -0.5f, 0.0f, d,

       -0.5f, 0.0f, d,
       -0.5f, -2.0f, d, 
       -0.5f, -2.0f, 0.0f, 

    };
    static const GLfloat wall_i[] = {
       -2.0f, -3.0f, 0.0f,
       -0.5f, -2.0f, 0.0f, 
       -0.5f, -2.0f, d,

      -2.0f, -3.0f, 0.0f,
       -2.0f, -3.0f, d, 
       -0.5f, -2.0f, d,
    };
    static const GLfloat wall_j[] = {
       2.0f, -3.0f, 0.0f,
       0.5f, -2.0f, 0.0f, 
       0.5f, -2.0f, d,

      2.0f, -3.0f, 0.0f,
      2.0f, -3.0f, d, 
      0.5f, -2.0f, d,
    };
    static const GLfloat wall_k[] = {
       2.0f, -3.0f, 0.0f,
       -2.0f, -3.0f, 0.0f,
       -2.0f, -3.0f, d,
       

      2.0f, -3.0f, d,
      2.0f, -3.0f, 0.0f,
       -2.0f, -3.0f, d,
    };
    

    this->object0 = create3DObject(GL_TRIANGLES, 3, buffer_0, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, buffer_1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, buffer_2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, buffer_3, color, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, buffer_4, color, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 3, buffer_5, color, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 3, buffer_6, color, GL_FILL);

    this->object7 = create3DObject(GL_TRIANGLES, 3, buffer_7, color2, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 6, buffer_8, color2, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, 3, buffer_9, color2, GL_FILL);
    this->object10 = create3DObject(GL_TRIANGLES, 3, buffer_10, color2, GL_FILL);
    this->object11 = create3DObject(GL_TRIANGLES, 3, buffer_11, color2, GL_FILL);
    this->object12 = create3DObject(GL_TRIANGLES, 3, buffer_12, color2, GL_FILL);
    this->object13 = create3DObject(GL_TRIANGLES, 3, buffer_13, color2, GL_FILL);

    this->walla   = create3DObject(GL_TRIANGLES, 6, wall_a, color, GL_FILL);
    this->wallb   = create3DObject(GL_TRIANGLES, 6, wall_b, color, GL_FILL);
    this->wallc   = create3DObject(GL_TRIANGLES, 6, wall_c, color, GL_FILL);
    this->walld   = create3DObject(GL_TRIANGLES, 6, wall_d, color, GL_FILL);
    this->walle   = create3DObject(GL_TRIANGLES, 6, wall_e, color, GL_FILL);
    this->wallf   = create3DObject(GL_TRIANGLES, 6, wall_f, color, GL_FILL);
    this->wallg   = create3DObject(GL_TRIANGLES, 6, wall_g, color2, GL_FILL);
    this->wallh   = create3DObject(GL_TRIANGLES, 6, wall_h, color2, GL_FILL);
    this->walli   = create3DObject(GL_TRIANGLES, 6, wall_i, color, GL_FILL);
    this->wallj   = create3DObject(GL_TRIANGLES, 6, wall_j, color, GL_FILL);
    this->wallk   = create3DObject(GL_TRIANGLES, 6, wall_k, color, GL_FILL);

}



void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 0, 1));
   // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
   //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
   Matrices.model *= (translate * rotate1 * rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object0);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
    draw3DObject(this->object8);
    draw3DObject(this->object9);
    draw3DObject(this->object10);
    draw3DObject(this->object11);
    draw3DObject(this->object12);
    draw3DObject(this->object13);
    draw3DObject(this->walla);
    draw3DObject(this->wallb);
    draw3DObject(this->wallc);
    draw3DObject(this->walld);
    draw3DObject(this->walle);
    draw3DObject(this->wallf);
    draw3DObject(this->wallg);
    draw3DObject(this->wallh);
    draw3DObject(this->walli);
    draw3DObject(this->wallj);
    draw3DObject(this->wallk);

}

void Plane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {
   // if(this->position.z > 0){
   //    this->position.z -= 0.1;
   //    this->gravity = true;
   // }
   // else  
   //    this->gravity = false;

        

}

