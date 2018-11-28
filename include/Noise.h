#ifndef NOISE_H
#define NOISE_H
#define HASHSCALE1 .1031
#define HASHSCALE3 glm::vec3(.1031, .1030, .0973)
#define HASHSCALE4 glm::vec4(.1031, .1030, .0973, .1099)
#include <glm/glm.hpp>

namespace Noise
{
extern glm::mat2 m;

    float hash11(float p);


//----------------------------------------------------------------------------------------
//  1 out, 2 in...
float hash12(glm::vec2 p);


//----------------------------------------------------------------------------------------
//  1 out, 3 in...
float hash13(glm::vec3 p3);


//----------------------------------------------------------------------------------------
//  2 out, 1 in...
//vec2 hash21(float p)
//{
//	vec3 p3 = fract(vec3(p) * HASHSCALE3);
//	p3 += dot(p3, p3.yzx + 19.19);
//    return fract((p3.xx+p3.yz)*p3.zy);
//
//}
//
////----------------------------------------------------------------------------------------
/////  2 out, 2 in...
//vec2 hash22(vec2 p)
//{
//	vec3 p3 = fract(vec3(p.xyx) * HASHSCALE3);
//    p3 += dot(p3, p3.yzx+19.19);
//    return fract((p3.xx+p3.yz)*p3.zy);
//
//}
//
////----------------------------------------------------------------------------------------
/////  2 out, 3 in...
//vec2 hash23(vec3 p3)
//{
//	p3 = fract(p3 * HASHSCALE3);
//    p3 += dot(p3, p3.yzx+19.19);
//    return fract((p3.xx+p3.yz)*p3.zy);
//}
//
////----------------------------------------------------------------------------------------
////  3 out, 1 in...
//vec3 hash31(float p)
//{
//   vec3 p3 = fract(vec3(p) * HASHSCALE3);
//   p3 += dot(p3, p3.yzx+19.19);
//   return fract((p3.xxy+p3.yzz)*p3.zyx);
//}
//
//
////----------------------------------------------------------------------------------------
/////  3 out, 2 in...
//vec3 hash32(vec2 p)
//{
//	vec3 p3 = fract(vec3(p.xyx) * HASHSCALE3);
//    p3 += dot(p3, p3.yxz+19.19);
//    return fract((p3.xxy+p3.yzz)*p3.zyx);
//}
//
////----------------------------------------------------------------------------------------
/////  3 out, 3 in...
glm::vec3 hash33(glm::vec3 p3);

//
////----------------------------------------------------------------------------------------
//// 4 out, 1 in...
//vec4 hash41(float p)
//{
//	vec4 p4 = fract(vec4(p) * HASHSCALE4);
//    p4 += dot(p4, p4.wzxy+19.19);
//    return fract((p4.xxyz+p4.yzzw)*p4.zywx);
//
//}
//
////----------------------------------------------------------------------------------------
//// 4 out, 2 in...
//vec4 hash42(vec2 p)
//{
//	vec4 p4 = fract(vec4(p.xyxy) * HASHSCALE4);
//    p4 += dot(p4, p4.wzxy+19.19);
//    return fract((p4.xxyz+p4.yzzw)*p4.zywx);
//
//}
//
////----------------------------------------------------------------------------------------
//// 4 out, 3 in...
//vec4 hash43(vec3 p)
//{
//	vec4 p4 = fract(vec4(p.xyzx)  * HASHSCALE4);
//    p4 += dot(p4, p4.wzxy+19.19);
//    return fract((p4.xxyz+p4.yzzw)*p4.zywx);
//}
//
////----------------------------------------------------------------------------------------
//// 4 out, 4 in...
//vec4 hash44(vec4 p4)
//{
//	p4 = fract(p4  * HASHSCALE4);
//    p4 += dot(p4, p4.wzxy+19.19);
//    return fract((p4.xxyz+p4.yzzw)*p4.zywx);
//}






glm::vec3 noised2(glm::vec2 x );



float terrain(glm::vec2 p );
float noise3(glm::vec3 x);







}

#endif // NOISE_H
