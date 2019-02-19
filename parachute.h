#include "main.h"
#include "missile.h"
class Parachute {
    public:
        Parachute() {}
        Parachute(float x, float y, float z, int index);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        float R;
        float height;
        float r;
        float index;
        bool isShot(Missile m);
        bool shot;
        void tick();
    private:
        VAO *object;
};