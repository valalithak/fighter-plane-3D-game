#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "water.h"
#include "score.h"
#include "obstacle.h"
#include "bomb.h"
#include "fuel.h"
#include "arrow.h"
#include "smokering.h"
#include "missile.h"
#include "parachute.h"
#include "volcano.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
#define NUM_OBSTACLES 100

Ball fuel_powerup;
Plane plane;
Water water;
Obstacle obs[NUM_OBSTACLES];
Score sc[3];
Score alt[3];
Bomb bomb;
Missile mis;
Fuel fuel_bar;
Arrow arrow[NUM_OBSTACLES];
Arrow direction;
Smokering sring;
Parachute par;
Volcano volc[NUM_OBSTACLES];


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int view = 0;
int score = plane.speed;
int scu, sct, sch;
int altu, altt, alth;
int fuel = 2000;
int altitude = 100;
int jump = 0;
int ring_pass = 0;
int check = 0;
float to_x = 0;
float to_y = 0;
float to_z = 0;
int bonus = 0;
int volcano_flag = 0;
Timer t60(1.0 / 60);

void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    if (view == 0) //follow cam
    {

        float angle = (plane.pitch * 3.14) / 180;

        glm::vec3 eye(plane.position.x, plane.position.y - 15, plane.position.z + 5);

        glm::vec3 target(plane.position.x, plane.position.y, plane.position.z);
        glm::vec3 up(0, 0, 1);
        Matrices.view = glm::lookAt(eye, target, up);
    }

    else if (view == 1) // first person plane view
    {
        float angle = (plane.rotation * 3.14) / 180;

        glm::vec3 eye(plane.position.x + 2 * sin(angle), plane.position.y, plane.position.z + 2 * cos(angle));
        glm::vec3 target(plane.position.x, plane.position.y + 1.2, plane.position.z);
        glm::vec3 up(0, 1, 0);
        Matrices.view = glm::lookAt(eye, target, up);
    }

    else if (view == 2) // tower-view
    {

        glm::vec3 target(plane.position.x, plane.position.y, plane.position.z);
        glm::vec3 eye(3, 3, 3);
        glm::vec3 up(0, 0, 1);
        Matrices.view = glm::lookAt(eye, target, up);
    }

    else if (view == 3) // top view
    {

        glm::vec3 eye(plane.position.x, plane.position.y, plane.position.z + 5);
        glm::vec3 target(plane.position.x, plane.position.y, plane.position.z);
        glm::vec3 up(0, 1, 0);
        Matrices.view = glm::lookAt(eye, target, up);
    }

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render

    water.draw(VP);
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (obs[i].shot == false)
            obs[i].draw(VP);
    }
    if (view == 0 || view == 1 || view == 3)
    {
        sc[0].draw(VP);
        sc[1].draw(VP);
        sc[2].draw(VP);
        alt[0].draw(VP);
        alt[1].draw(VP);
        alt[2].draw(VP);
        fuel_bar.draw(VP);

        for (int j = 3; j < NUM_OBSTACLES; j++)
        {
            if (obs[j].shot == false)
            {
                arrow[j].draw(VP);
                check = j;
                break;
            }
            else
                continue;
        }
    }

    if (bomb.appear)
        bomb.draw(VP);
    if (view != 1)
        plane.draw(VP);

    sring.draw(VP);
    if (mis.shot == true)
        mis.draw(VP);

    if (fuel_powerup.taken == false)
        fuel_powerup.draw(VP);
    if (par.shot == false)
        par.draw(VP);
    //direction.draw(VP);
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (i % 10 == 0)
        {
            volc[i].draw(VP);
        }
    }
}

void tick_input(GLFWwindow *window)
{
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int t = glfwGetKey(window, GLFW_KEY_T);
    int zero = glfwGetKey(window, GLFW_KEY_0);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    if (three)
        view = 3;
    if (one)
        view = 1;
    if (two)
        view = 2;
    if (zero)
        view = 0;
    if (a)
        plane.pitch -= 1;
    if (d)
        plane.pitch += 1;

    if (altitude > 110)
    {
        plane.gravity = true;
    }
    if (altitude <= 110)
    {
        plane.gravity = false;
    }
    if (space)
        plane.loopback = true;

    if (up)
    {

        altitude += 3;

        plane.position.z += plane.speed / 20;
        if (view == 0)
        {
            sc[0].position.z = plane.position.z;
            sc[1].position.z = plane.position.z;
            sc[2].position.z = plane.position.z;
            alt[0].position.z = plane.position.z;
            alt[1].position.z = plane.position.z;
            alt[2].position.z = plane.position.z;
            fuel_bar.position.x = sc[1].position.x;
            fuel_bar.position.y = sc[1].position.y - 2;
            fuel_bar.position.z = sc[1].position.z;
        }
    }
    if (down)
    {

        altitude -= 3;

        plane.position.z -= plane.speed / 20;
        if (view == 0)
        {
            sc[0].position.z = plane.position.z;
            sc[1].position.z = plane.position.z;
            sc[2].position.z = plane.position.z;
            alt[0].position.z = plane.position.z;
            alt[1].position.z = plane.position.z;
            alt[2].position.z = plane.position.z;
            fuel_bar.position.x = sc[1].position.x;
            fuel_bar.position.y = sc[1].position.y - 2;
            fuel_bar.position.z = sc[1].position.z;
        }
    }

    if (q)
    {
        plane.yaw += 1;
        if (view == 0)
        {

            sc[0].position.x = plane.position.x;
            sc[0].position.z = plane.position.z;
            sc[1].position.x = sc[0].position.x - 1;
            sc[1].position.z = sc[0].position.z;
            sc[2].position.x = sc[1].position.x - 1;
            sc[2].position.z = sc[1].position.z;

            alt[0].position.x = plane.position.x + 5;
            alt[0].position.z = plane.position.z;

            alt[1].position.x = alt[0].position.x - 1;
            alt[1].position.z = alt[0].position.z;

            alt[2].position.x = alt[1].position.x - 1;
            alt[2].position.z = alt[1].position.z;

            fuel_bar.position.x = sc[1].position.x;
            fuel_bar.position.y = sc[1].position.y - 2;
            fuel_bar.position.z = sc[1].position.z;
        }
    }
    if (e)
    {

        plane.yaw -= 1;
        if (view == 0)
        {

            sc[0].position.x = plane.position.x;
            sc[0].position.z = plane.position.z;

            sc[1].position.x = sc[0].position.x - 1;
            sc[1].position.z = sc[0].position.z;

            sc[2].position.x = sc[1].position.x - 1;
            sc[2].position.z = sc[1].position.z;

            alt[0].position.x = plane.position.x + 5;
            alt[0].position.z = plane.position.z;

            alt[1].position.x = alt[0].position.x - 1;
            alt[1].position.z = alt[0].position.z;

            alt[2].position.x = alt[1].position.x - 1;
            alt[2].position.z = alt[1].position.z;

            fuel_bar.position.x = sc[1].position.x;
            fuel_bar.position.y = sc[1].position.y - 2;
            fuel_bar.position.z = sc[1].position.z;
        }
    }

    if (t)
    {
        bomb.appear = true;
        bomb.position.x = plane.position.x;
        bomb.position.y = plane.position.y - 2;
        bomb.position.z = plane.position.z;
    }
    if (m)
    {
        mis.shot = true;
        mis.position.x = plane.position.x;
        mis.position.y = plane.position.y;
        mis.position.z = plane.position.z;
    }

    if (w) // moves forward
    {
        plane.speed += 0.01;
        float a = (plane.yaw * 3.14) / 180;
        plane.position.y += 0.1 * cos(a);
        plane.position.x -= 0.1 * sin(a);
        if (view == 0)
        {
            sc[0].position.x -= 0.1 * sin(a);
            sc[1].position.x -= 0.1 * sin(a);
            sc[2].position.x -= 0.1 * sin(a);
            if (cos(a) > 0)
            {
                sc[0].position.y = plane.position.y - 5 * cos(a) - 5;
                sc[1].position.y = plane.position.y - 5 * cos(a) - 5;
                sc[2].position.y = plane.position.y - 5 * cos(a) - 5;
                alt[0].position.y = plane.position.y - 5 * cos(a) - 5;
                alt[1].position.y = plane.position.y - 5 * cos(a) - 5;
                alt[2].position.y = plane.position.y - 5 * cos(a) - 5;
                fuel_bar.position.x = sc[1].position.x;
                fuel_bar.position.y = sc[1].position.y - 2;
                fuel_bar.position.z = sc[1].position.z;
            }
            else
            {
                sc[0].position.y = plane.position.y - 5 * cos(a) + 5;
                sc[1].position.y = plane.position.y - 5 * cos(a) + 5;
                sc[2].position.y = plane.position.y - 5 * cos(a) + 5;
                alt[0].position.y = plane.position.y - 5 * cos(a) + 5;
                alt[1].position.y = plane.position.y - 5 * cos(a) + 5;
                alt[2].position.y = plane.position.y - 5 * cos(a) + 5;
                fuel_bar.position.x = sc[1].position.x;
                fuel_bar.position.y = sc[1].position.y - 2;
                fuel_bar.position.z = sc[1].position.z;
            }
        }
    }
    if (!w)
    {
        if (score > 10)
            plane.speed -= 0.005;
    }
}

void tick_elements()
{

    if(plane.lives<=0) {
        quit(window);
    }
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if(i%10==0)
        {
            bool v = obs[i].Check_NoFlying(plane);
            if(v)
            {    
                cout << "DEAD at "  << altitude << endl;
                plane.lives--;
                v = false;
            }
        }
    }
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (i % 10 == 0)
        {
            volc[i].position.x = obs[i].position.x;
            volc[i].position.y = obs[i].position.y;
            volc[i].position.z = obs[i].position.z + 3;
        }
    }
    par.tick();

    if (mis.shot == true)
    {

        bool coll = obs[check].tick_m(mis);
        if (coll == true && obs[check].shot == false)
        {
            obs[check].shot = true;
            mis.shot = false;
            cout << "missile hit" << endl;
        }
        bool coll2 = par.isShot(mis);
        if (coll2 == true && par.shot == false)
        {
            par.shot = true;
            mis.shot = false;
            bonus += 10;
            cout << "parachute hit" << endl;
        }
    }
    if (fuel_powerup.taken == false)
    {

        bool coll = fuel_powerup.tick_plane(plane);
        if (coll == true)
        {
            fuel_powerup.taken = true;
            fuel = 2000;
            cout << "fuelled" << endl;
        }
    }
    if (bomb.appear == true)
    {

        bool coll = obs[check].tick_b(bomb);
        if (coll == true && obs[check].shot == false)
        {
            obs[check].shot = true;
            bomb.appear = false;
            cout << "bomb hit" << endl;
        }
    }
    bool ring_pass_bool = sring.isPlane(plane);
    if (ring_pass == 0 && ring_pass_bool == 1)
    {
        bonus += 10;
        ring_pass = 1;
    }
    plane.tick();
    if (bomb.appear)
    {
        bomb.tick();
        cout << bomb.position.x << " " << bomb.position.y << " " << bomb.position.z << endl;
        cout << obs[check].position.x << " " << obs[check].position.y << " " << obs[check].position.z << endl;
        cout << endl;
    }
    mis.tick(plane);
    for (int j = 0; j < NUM_OBSTACLES; j++)
    {
        if (view == 0)
        {
            arrow[j].position.x = obs[j].position.x;
            arrow[j].position.y = obs[j].position.y;
            arrow[j].position.z = obs[j].position.z + 4;
        }
    }

    if (plane.speed * 10 <= 999)
        score = plane.speed * 10;
    else
        score = 999;

    scu = score % 10;
    sct = (score / 10) % 10;
    sch = (score / 100) % 10;
    sc[0].val = scu;
    sc[1].val = sct;
    sc[2].val = sch;

    if (altitude >= 999)
        altitude = 999;

    altu = altitude % 10;
    altt = (altitude / 10) % 10;
    alth = (altitude / 100) % 10;
    alt[0].val = altu;
    alt[1].val = altt;
    alt[2].val = alth;

    fuel -= 0.01;
    fuel_bar.f = fuel;

    fuel_bar.position.x = sc[1].position.x;
    fuel_bar.position.y = sc[1].position.y - 2;
    fuel_bar.position.z = sc[1].position.z;

    alt[0].position.x = sc[0].position.x + 5;
    alt[1].position.x = sc[1].position.x + 5;
    alt[2].position.x = sc[2].position.x + 5;
    alt[0].position.y = sc[0].position.y;
    alt[0].position.z = sc[0].position.z;
    alt[1].position.y = sc[0].position.y;
    alt[2].position.z = sc[0].position.z;

    if (view == 1)
    {
        sc[0].position.x = plane.position.x - 2;
        sc[0].position.y = plane.position.y + 1.5;
        sc[0].position.z = plane.position.z - 0.5;

        sc[1].position.x = sc[0].position.x - 1;
        sc[1].position.y = sc[0].position.y;
        sc[1].position.z = sc[0].position.z;

        sc[2].position.x = sc[1].position.x - 1;
        sc[2].position.y = sc[1].position.y;
        sc[2].position.z = sc[1].position.z;

        alt[0].position.x = sc[0].position.x + 5;
        alt[1].position.x = sc[1].position.x + 5;
        alt[2].position.x = sc[2].position.x + 5;
        alt[0].position.y = sc[0].position.y;
        alt[0].position.z = sc[0].position.z;

        alt[1].position.y = sc[0].position.y;
        alt[1].position.z = sc[1].position.z;
        alt[2].position.y = sc[2].position.y;
        alt[2].position.z = sc[2].position.z;
    }

    if (view == 3)
    {
        sc[0].position.x = plane.position.x - 3;
        sc[0].position.y = plane.position.y - 3;
        sc[0].position.z = plane.position.z - 0.5;

        sc[1].position.x = sc[0].position.x - 1;
        sc[1].position.y = sc[0].position.y;
        sc[1].position.z = sc[0].position.z;

        sc[2].position.x = sc[1].position.x - 1;
        sc[2].position.y = sc[1].position.y;
        sc[2].position.z = sc[1].position.z;

        alt[0].position.x = sc[0].position.x + 7;
        alt[1].position.x = sc[1].position.x + 7;
        alt[2].position.x = sc[2].position.x + 7;
        alt[0].position.y = sc[0].position.y;
        alt[0].position.z = sc[0].position.z;

        alt[1].position.y = sc[0].position.y;
        alt[1].position.z = sc[1].position.z;
        alt[2].position.y = sc[2].position.y;
        alt[2].position.z = sc[2].position.z;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    fuel_powerup = Ball(-3, 25, COLOR_YELLOW);
    water = Water(0, 0, COLOR_WATER);
    plane = Plane(0, 0, 0, COLOR_GREY, COLOR_GREY);
    bomb = Bomb(0, 0, 0, 0.5, COLOR_BLACK);
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (i % 2 == 0)
            obs[i] = Obstacle(-80 + (10 * i), (16 * i), -3, i, COLOR_GOLD);
        arrow[i] = Arrow(2 * i + rand() % 6, -5, -1 * (i + rand() % 2) + 0.5, i);
        if (i % 2 == 1)
            obs[i] = Obstacle(30 - (i - NUM_OBSTACLES / 2), 20 * i, -3, i, COLOR_GOLD);
    }
    sc[0] = Score(screen_center_x, -8, -2, scu, COLOR_BLACK);
    sc[1] = Score(screen_center_x - 1, -8, -2, sct, COLOR_BLACK);
    sc[2] = Score(screen_center_x - 2, -8, -2, sch, COLOR_BLACK);

    alt[0] = Score(screen_center_x + 5, -8, -2, altu, COLOR_BLACK);
    alt[1] = Score(screen_center_x - 1 + 5, -8, -2, altt, COLOR_BLACK);
    alt[2] = Score(screen_center_x - 2 + 5, -8, -2, alth, COLOR_BLACK);

    fuel_bar = Fuel(screen_center_x, -10, -2, fuel, COLOR_GREEN, COLOR_DARKRED);
    sring = Smokering(0, 200, 10, COLOR_LIGHTGREY);
    mis = Missile(0, 4, 0, 0.1, COLOR_FIRE);
    direction = Arrow(0, 0, 0, 0);
    par = Parachute(0, 300, 15, 0);

    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        volc[i] = Volcano(0, 0, 0, i);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");

    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv)
{
    srand(time(0));
    int width = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            char titleString[128];
            sprintf(titleString, "Bonus : %d", bonus);

            glfwSetWindowTitle(window, titleString);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    // Matrices.projection = glm::perspective(left, right, bottom, top);
    Matrices.projection = glm::infinitePerspective(glm::radians(90.0f), 2.0f, 0.1f);
}
