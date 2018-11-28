#ifndef GPUMARCHINGCUBES_H
#define GPUMARCHINGCUBES_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
namespace GPUMarchingCubes
{
    extern GLuint shaderTest;
    extern GLuint shader1;
    extern GLuint shader2;
    extern GLuint shader3;
    extern GLuint gridSSBO;
    extern GLuint pointCounter;
    extern GLuint marchableCounter;
    extern GLuint marchableList;
    extern GLuint triangleCounter;
    extern GLuint testAtomic;
    extern GLuint triTableBuffer;

    extern GLuint s1Stride;
    extern GLuint s1Pos;
    extern GLuint s3Stride;
    extern GLuint s3Pos;

    extern int triTable[4096];
    void init();
    GLuint generateChunk(glm::vec3 pos,float stride,GLuint &vertexBuffer, GLuint &normalBuffer);
}

#endif // GPUMARCHINGCUBES_H
