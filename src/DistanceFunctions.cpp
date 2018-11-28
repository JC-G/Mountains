#include "DistanceFunctions.h"
#include <vector>
namespace DistanceFunctions
{
float TEST(glm::vec3 inPos)
{

    inPos += Noise::hash33(inPos/glm::vec3(1000.))*glm::vec3(50.);
    float MH = 20;
    //return -1;
    //float t1=glm::min(torus(inPos,glm::vec3(50),30,10),torus(glm::vec3(inPos.x,inPos.z,inPos.y),glm::vec3(80,50,50),30,10));
    if (inPos.y > MH+20)
    {
        //return 10000;
    }

    float terrain=0;// = inPos.y-10.;
    float s=1;
    float h=1;
    for (int i = 0; i < 5;i++)
    {
    terrain += Noise::noise3(inPos*glm::vec3(s*0.05))*h;
    s*=2; h/=2;

    }
    return terrain+(inPos.y-10.)*0.1-2-Noise::terrain(glm::vec2(inPos.x,inPos.z)/glm::vec2(30.))*3.;


}

}
float DistanceFunctions::torus(glm::vec3 inPos, glm::vec3 origin, float R, float r)
{
    inPos -= origin;
    //inPos.x *= 1.5;
    glm::vec2 tmp(inPos.x,inPos.y);

    float p1 = glm::length(tmp)-R;
    return p1*p1+inPos.z*inPos.z -r*r;

}
