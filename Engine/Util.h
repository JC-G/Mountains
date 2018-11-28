#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>
#include <glm/glm.hpp>
namespace Util
{
    GLuint LoadShaders(const char* vertex_file_path, const char* frag_file_path);
        std::string ReadShaderFile(const char* path);
        GLuint loadBMP(const char* file_path, bool is2D);
        GLuint LoadComputeShader(const char* file_path,bool includeSDF);
}

#endif // UTIL_H
