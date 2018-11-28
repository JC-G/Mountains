#ifndef DISTANCEFUNCTIONS_H
#define DISTANCEFUNCTIONS_H
#include "Noise.h"
#include <glm/glm.hpp>
namespace DistanceFunctions
{
    float TEST(glm::vec3 inPos);
    float torus(glm::vec3 inPos, glm::vec3 origin, float R, float r);
}

#endif // DISTANCEFUNCTIONS_H
