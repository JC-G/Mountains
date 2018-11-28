#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
Camera::Camera()
{
    pos=glm::vec3(857.408, 363, 663.721);

    //ctor
}

Camera::~Camera()
{
    //dtor
}
void Camera::updatePos()
{

    direction = glm::vec3(cos(rotation[1])*sin(rotation[0]),
                                       sin(rotation[1]),
                                       cos(rotation[1]) * cos(rotation[0]));


    lookPos = pos+direction;
    //std::cout << direction.x << "|" << direction.y << "|" << direction.z << std::endl;
}


glm::mat4 Camera::getViewMatrix()
{
    updatePos();
    return glm::lookAt(pos,lookPos,glm::vec3(0,1,0));
}
