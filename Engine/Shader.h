#ifndef SHADER_H
#define SHADER_H
#include <map>
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
class Shader
{
    public:
        GLuint ID;
        Shader(const char* vert, const char* frag);
        std::map<std::string,GLuint> Uniforms;

    protected:

    private:
};

#endif // SHADER_H
