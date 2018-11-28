#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
    public:
        glm::mat4 getViewMatrix();
        glm::vec3 pos;
        glm::vec3 lookPos;
        glm::vec3 rotation;
        glm::vec3 direction;
        glm::vec3 hDirection;
        glm::vec3 right;
        float FOV = 60;

        Camera();
        void updatePos();
        virtual ~Camera();

    protected:

    private:
};

#endif // CAMERA_H
