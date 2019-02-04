#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

//Ball ball1;
Plane plane;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int view = 0;
int score = 0;
float cam_distance = 100;
float tilt_angle = 0;
float angle = 30;

Timer t60(1.0 / 60);

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    glm::vec3 up (0, 1, 0);

    if(view==0) // top view
    {
        float r = cam_distance*cos(angle*M_PI/180.0f);
        float angle = plane.rotation + tilt_angle;
        glm::vec3 eye (plane.position.x - r*sin(angle*M_PI/180.0f) , plane.position.y + cam_distance*sin(angle*M_PI/180.0f), plane.position.z + r*cos(angle*M_PI/180.0f));
        glm::vec3 target (plane.position.x, plane.position.y, plane.position.z);
        Matrices.view = glm::lookAt( eye, target, up );
        

    }

    else if(view==1) // first person plane view
    {
        glm::vec3 eye (plane.position.x, plane.position.y+5, plane.position.z);
        glm::vec3 target (plane.position.x + 100*sin(plane.rotation*M_PI/180.0f), plane.position.y, plane.position.z - 100*cos(plane.rotation*M_PI/180.0f));
        Matrices.view = glm::lookAt( eye, target, up ); 
    }


    else if(view==2) // tower-view
    {

        
        glm::vec3 target (plane.position.x, plane.position.y, plane.position.z);
        glm::vec3 eye (10, 20, 3);
        Matrices.view = glm::lookAt( eye, target, up );
    }


    else if(view==3) // follow cam view
    {
        glm::vec3 eye (plane.position.x, plane.position.y-5, plane.position.z+0.6);
        glm::vec3 target (plane.position.x, plane.position.y, plane.position.z);
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
    if(t)
    {

            if(view==3)
                view = 0;
                
            else if(view==2)
                view = 3;
            else if(view==1)
                view = 2;
            else if(view==0)
                view = 1;
        
    }
}

void tick_elements() {
    
    //if(plane.health<=0.0) {
      //  quit(window);
    //}
    plane.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    //ball1       = Ball(0, 0, COLOR_RED);
    plane       = Plane(0, 0, 0, COLOR_BLACK, COLOR_RED);


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
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
