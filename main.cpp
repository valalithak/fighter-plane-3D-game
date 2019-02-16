#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "water.h"
#include "score.h"
#include "obstacle.h"
#include "bomb.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

//Ball ball1;
Plane plane;
Water water;
Obstacle obs[20];
Score sc[3];
Bomb bomb;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int view = 0;
int score = plane.speed*100 +10;
int scu, sct, sch;
Timer t60(1.0 / 60);

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);
    

    if(view==0) //follow cam
    {
        
      float angle = (plane.pitch*3.14)/180;
      
      glm::vec3 eye ( plane.position.x, plane.position.y-15, plane.position.z+5);
      
      glm::vec3 target ( plane.position.x, plane.position.y , plane.position.z);
      glm::vec3 up (0, 0, 1);
      Matrices.view = glm::lookAt( eye, target, up );
      

    }

    else if(view==1) // first person plane view
    {
        float angle = (plane.rotation*3.14)/180;

       
        glm::vec3 eye ( plane.position.x+2*sin(angle), plane.position.y, plane.position.z+2*cos(angle));
        glm::vec3 target ( plane.position.x, plane.position.y+1.2, plane.position.z-0.6);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
        
        
    }

    else if(view==2) // tower-view
    {
     
        glm::vec3 target (plane.position.x, plane.position.y, plane.position.z);
        glm::vec3 eye (3, 3, 3);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up );

    }


    else if(view==3) // top view
    {
        
        glm::vec3 eye (plane.position.x, plane.position.y, plane.position.z+5);
        glm::vec3 target (plane.position.x, plane.position.y, plane.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); 
        
    }

   

    
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    //ball1.draw(VP);
   
    water.draw(VP);
    for(int i=0; i<20; i++)
    obs[i].draw(VP);
    if(view==0)
    {
        sc[0].draw(VP);
        sc[1].draw(VP);
        sc[2].draw(VP);
    }
    if(bomb.appear) 
        bomb.draw(VP);
    if(view!=1)
         plane.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int t = glfwGetKey(window, GLFW_KEY_T);
    int zero = glfwGetKey(window, GLFW_KEY_0);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    if(three)
        view = 3;
    if(one)
        view = 1;
    if(two)
        view = 2;
    if(zero)
        view = 0;
    if(left)
        plane.pitch -= 1;
    if(right)
         plane.pitch += 1;
    if (q) {
        plane.roll += 1;
    }

    if (w)
    {
        plane.speed += 0.01;
        plane.position.z += plane.speed;
        sc[0].position.z = plane.position.z;
        sc[1].position.z = plane.position.z;
        sc[2].position.z = plane.position.z;
    }
       
    if (a) {
        plane.position.x -= 0.1 * cos(plane.pitch * M_PI / 180);
        plane.position.z -= 0.1 * sin(plane.pitch * M_PI / 180);
        sc[0].position.x = plane.position.x;
        sc[0].position.z = plane.position.z;
        sc[1].position.x = sc[0].position.x - 1;
        sc[1].position.z = sc[0].position.z;
        sc[2].position.x = sc[1].position.x - 1;
        sc[2].position.z = sc[1].position.z;


    }
    if (d) {
        plane.position.x += 0.1 * cos(plane.pitch * M_PI / 180);
        plane.position.z -= 0.1 * sin(plane.pitch * M_PI / 180);
        sc[0].position.x = plane.position.x;
        sc[0].position.z = plane.position.z;
        sc[1].position.x = sc[0].position.x - 1;
        sc[1].position.z = sc[0].position.z;
        sc[2].position.x = sc[1].position.x - 1;
        sc[2].position.z = sc[1].position.z;
    }
    
    if(t)
    {
        bomb.appear = true;
        bomb.position.x = plane.position.x;
        bomb.position.y = plane.position.y -2;
        bomb.position.z = obs[0].position.z;
    }
    if(up)
    {
        plane.position.y += 0.2;
        sc[0].position.y = plane.position.y - 5;
        sc[1].position.y = plane.position.y - 5;
        sc[2].position.y = plane.position.y - 5;

    }


        
}

void tick_elements() {
    
    //if(plane.health<=0.0) {
      //  quit(window);
    //}
    plane.tick();
    cout << "x water plane obs0 " << water.position.x << " "  << plane.position.x << " " << obs[0].position.x << endl;
    cout << "y water plane obs0 " << water.position.y << " "  << plane.position.y << " " << obs[0].position.y << endl;
    cout << "z water plane obs0 " << water.position.z << " "  << plane.position.z << " " << obs[0].position.z << endl;
    if(plane.speed*10 <= 999)
        score = plane.speed*10;
    else
        score = 999;    

    scu = score%10;
    sct = (score/10)%10;
    sch = (score/100)%10; 
    sc[0].val = scu;
    sc[1].val = sct;
    sc[2].val = sch;
    
   
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    //ball1       = Ball(0, 0, COLOR_RED);
    water       = Water(0, 0, COLOR_WATER);
    plane       = Plane(0, 0, 0, COLOR_GREY, COLOR_GREY);
    bomb        = Bomb(0, 0, 0, 0.5, COLOR_BLACK);
    for(int i=0; i<10; i++)
    {
        obs[i]         = Obstacle(2*i + rand()%6, 0, -1*(i+rand()%2), COLOR_GREEN);
    }
    for(int i=10; i<20; i++)
    {
        obs[i]         = Obstacle(-2*(i-10) + rand()%6, 0, -1*((i-10)+rand()%2), COLOR_GREEN);
    }
    sc[0]       = Score(screen_center_x, -8, -2, scu, COLOR_BLACK);
    sc[1]       = Score(screen_center_x - 1, -8, -2, sct, COLOR_BLACK);
    sc[2]       = Score(screen_center_x - 2, -8, -2, sch, COLOR_BLACK);
    
    
    
    
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    // Matrices.projection = glm::perspective(left, right, bottom, top);
    Matrices.projection = glm::infinitePerspective(glm::radians(90.0f),2.0f,0.1f);
}

