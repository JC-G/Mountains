#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <stdio.h>
#include <stdlib.h>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>
#include "Camera.h"
#include "Shader.h"
#include <memory>
namespace GameWindow
{
    bool init_postProcess();

    bool init_gl();
    bool init_shaders();
    void handleInput();
    glm::mat4 getProjectionMatrix();
    extern GLFWwindow* mainWindow;
    extern GLuint FrameBuffer;
    extern GLuint RenderedTexture;
    extern GLuint DepthRenderBuffer;
    extern GLuint quad_VertexArrayID;
    extern GLuint quad_vertexbuffer;
    extern std::shared_ptr<Shader> activeShader;
    extern std::shared_ptr<Shader> PPShader;
    extern std::shared_ptr<Camera> activeCamera;
    extern int width;
    extern int height;
    extern bool fullscreen;

}

#endif // GAMEWINDOW_H
