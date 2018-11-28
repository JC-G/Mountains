#include "Noise.h"

namespace Noise
{
glm::mat2 m = glm::mat2(0.8,-0.6,0.6,0.8);

float hash11(float p)
{
    glm::vec3 p3  = glm::fract(glm::vec3(p) * glm::vec3(HASHSCALE1));
    p3 += glm::vec3(glm::dot(p3, glm::vec3(p3.y,p3.z,p3.x) + glm::vec3(19.19)));
    return glm::fract((p3.x + p3.y) * p3.z);
}

float hash12(glm::vec2 p)
{
    glm::vec3 p3  = glm::fract(glm::vec3(p.x,p.y,p.x) * glm::vec3(HASHSCALE1));
    p3 += glm::vec3(glm::dot(p3, glm::vec3(p3.y,p3.z,p3.x) + glm::vec3(19.19)));
    return glm::fract((p3.x + p3.y) * p3.z);
}


float hash13(glm::vec3 p3)
{
    p3  = glm::fract(p3 * glm::vec3(HASHSCALE1));
    p3 += glm::vec3(glm::dot(p3, glm::vec3(p3.y,p3.z,p3.x) + glm::vec3(19.19)));
    return glm::fract((p3.x + p3.y) * p3.z);
}


glm::vec3 noised2(glm::vec2 x )
{
    glm::vec2 f = glm::fract(x);
    glm::vec2 u = f*f*(glm::vec2(3.0)-glm::vec2(2.0)*f);

    // texel fetch version
    glm::vec2 p = glm::floor(x);
    float a = hash12(p+glm::vec2(0,0));
    float b = hash12(p+glm::vec2(1,0));
    float c = hash12(p+glm::vec2(0,1));
    float d = hash12(p+glm::vec2(1,1));


    return glm::vec3(a+(b-a)*u.x+(c-a)*u.y+(a-b-c+d)*u.x*u.y,
                     glm::vec2(6.0)*f*(glm::vec2(1.0)-f)*(glm::vec2(b-a,c-a)+glm::vec2(a-b-c+d)*glm::vec2(u.y,u.x)));
}


float terrain(glm::vec2 p )
{
    float a = 0.0;
    float b = 1.0;
    float t = 0;
    glm::vec2  d = glm::vec2(0.0);
    for( int i=0; i<8; i++ )
    {
        glm::vec3 n = noised2(p);
        d += glm::vec2(n.y,n.z);
        t+= b;
        a += b*n.x/(1.0+glm::dot(d,d));
        b *= 0.5;
        p = m*p*glm::vec2(2.0);
    }
    return a/t;
}

float noise3(glm::vec3 x)
{

    glm::vec3 p = glm::floor(x);
    glm::vec3 w = glm::fract(x);

    glm::vec3 u = w*w*w*(w*(w*glm::vec3(6.0)-glm::vec3(15.0))+glm::vec3(10.0));
    glm::vec3 du = glm::vec3(30.0)*w*w*(w*(w-glm::vec3(2.0))+glm::vec3(1.0));

    float a = hash13( p+glm::vec3(0,0,0) );
    float b = hash13( p+glm::vec3(1,0,0) );
    float c = hash13( p+glm::vec3(0,1,0) );
    float d = hash13( p+glm::vec3(1,1,0) );
    float e = hash13( p+glm::vec3(0,0,1) );
    float f = hash13( p+glm::vec3(1,0,1) );
    float g = hash13( p+glm::vec3(0,1,1) );
    float h = hash13( p+glm::vec3(1,1,1) );

    float k0 =   a;
    float k1 =   b - a;
    float k2 =   c - a;
    float k3 =   e - a;
    float k4 =   a - b - c + d;
    float k5 =   a - c - e + g;
    float k6 =   a - b - e + f;
    float k7 = - a + b + c - d + e - f - g + h;

    return  -1.0+2.0*(k0 + k1*u.x + k2*u.y + k3*u.z + k4*u.x*u.y + k5*u.y*u.z + k6*u.z*u.x + k7*u.x*u.y*u.z);


}


glm::vec3 hash33(glm::vec3 p3)
{
	p3 = glm::fract(p3 * HASHSCALE3);
    p3 += glm::dot(p3, glm::vec3(p3.y,p3.x,p3.z)+glm::vec3(19.19));
    return glm::fract((glm::vec3(p3.x,p3.x,p3.y) + glm::vec3(p3.y,p3.x,p3.x))*glm::vec3(p3.z,p3.y,p3.x));

}


}
