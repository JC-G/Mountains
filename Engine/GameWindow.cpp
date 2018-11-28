#include "GameWindow.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <iostream>
#include "Octree.h"
#include "MarchingChunkManager.h"
namespace GameWindow
{
GLuint FrameBuffer;
    GLuint RenderedTexture;
    GLuint DepthRenderBuffer;
    GLuint quad_VertexArrayID;
    GLuint quad_vertexbuffer;
    GLFWwindow* mainWindow;
    std::shared_ptr<Shader> activeShader;
    std::shared_ptr<Camera> activeCamera;
    std::shared_ptr<Shader> PPShader;
    int width=1280;
    int height=720;
    bool fullscreen = false;
bool init_postProcess()
{
    FrameBuffer = 0;
    glGenFramebuffers(1,&FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,FrameBuffer);

    glGenTextures(1,&RenderedTexture);
    glBindTexture(GL_TEXTURE_2D,RenderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, GameWindow::width, GameWindow::height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GLuint DepthRenderBuffer;
	glGenRenderbuffers(1, &DepthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, DepthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, GameWindow::width, GameWindow::height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthRenderBuffer);


    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,RenderedTexture,0);
    GLenum DrawBuffers[1];
    glDrawBuffers(1,DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "NOT COMPLETE";
        return false;
    }

    glGenVertexArrays(1, &quad_VertexArrayID);
    glBindVertexArray(quad_VertexArrayID);

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);



return true;

}
bool init_gl()
{
    if (!glfwInit())
    {
        return false;
    }
    //set the window constants
    glfwWindowHint(GLFW_SAMPLES,4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_REFRESH_RATE,60);


    glfwWindowHint(GLFW_VISIBLE,GLFW_TRUE);
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);
    mainWindow = glfwCreateWindow(width,height,"Test",/*glfwGetPrimaryMonitor()*/NULL,NULL);
    if(fullscreen)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(mainWindow,glfwGetPrimaryMonitor(),0,0,mode->width,mode->height,mode->refreshRate);

    }


    if (mainWindow == NULL)
    {
        printf("Window was not created");
        glfwTerminate();
        return false;
    }


    glfwMakeContextCurrent(mainWindow);
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        printf("GLEW was not loaded");
        return false;

    }
    glfwSetInputMode(mainWindow,GLFW_STICKY_KEYS,GL_TRUE);
    glfwSetInputMode(mainWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    //glEnable              ( GL_DEBUG_OUTPUT );
    //glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );

    glClearColor(0,148./255,1,1);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LESS);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    return true;
}

void handleInput()
{
    static double oldX,oldY;
    double X,Y;
    glfwGetCursorPos(mainWindow,&X,&Y);
    glfwSetCursorPos(mainWindow,width/2,height/2);
    double dX = width/2-X;
    double dY = height/2-Y;
    //oldY=Y;
    //oldX=X;

    activeCamera->rotation[0] += dX*0.01;
    activeCamera->rotation[1] += dY*0.01;
    activeCamera->rotation[1]=glm::clamp(activeCamera->rotation[1],(float)-1.57,(float)1.57);
    //std::cout << dX << "|" << dY << std::endl;
    activeCamera->updatePos();


    activeCamera->hDirection = glm::normalize(glm::vec3(activeCamera->direction.x,0,activeCamera->direction.z));
    activeCamera->right = glm::vec3(-cos(activeCamera->rotation[0]),0,sin(activeCamera->rotation[0]));//IFBREAK

    //activeCamera->right = glm::vec3(sin(activeCamera->rotation[0] - 3.14/2),0,cos(activeCamera->rotation[0]-3.14/2));

    if(glfwGetKey(mainWindow,GLFW_KEY_UP) || glfwGetKey(mainWindow,GLFW_KEY_W))
    {
        activeCamera->pos += activeCamera->hDirection;
        //activeCamera->shape->setLinearVelocity(btVector3(0,200,0));
        //activeCamera->shape->applyCentralForce(btVector3(0,1000,0));
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_DOWN) || glfwGetKey(mainWindow,GLFW_KEY_S))
    {
        activeCamera->pos -= activeCamera->hDirection;
        //activeCamera->shape->setLinearVelocity(btVector3(0,-2000,0));

        //activeCamera->shape->setLinearVelocity(btVector3(0,-2000,0));
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_LEFT) || glfwGetKey(mainWindow,GLFW_KEY_A))
    {
        activeCamera->pos -= activeCamera->right;
        //activeCamera->shape->setLinearVelocity(btVector3(999,0,0));

    }
    if (glfwGetKey(mainWindow,GLFW_KEY_RIGHT) || glfwGetKey(mainWindow,GLFW_KEY_D))
    {
        activeCamera->pos += activeCamera->right;
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_Z))
    {
        activeCamera->FOV += 5;
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_X))
    {
        activeCamera->FOV -= 5;
    }
    if(glfwGetKey(mainWindow,GLFW_KEY_SPACE))
    {
        activeCamera->pos += glm::vec3(0,1,0);
    }
    if(glfwGetKey(mainWindow,GLFW_KEY_LEFT_SHIFT))
    {
        activeCamera->pos -= glm::vec3(0,1,0);
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_I))
    {
        Octree::mainOctree->update(activeCamera->pos);
        //Octree::doUpdate = !Octree::doUpdate;
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_J))
    {
        //Octree::mainOctree->update(activeCamera->pos);
        Octree::doUpdate = !Octree::doUpdate;
        std::cout << Octree::doUpdate << std::endl;
    }
    if(glfwGetKey(mainWindow,GLFW_KEY_PERIOD))
    {
        std::cout << activeCamera->pos.x << ", " << activeCamera->pos.y << ", " << activeCamera->pos.z << std::endl;
    }
    if (glfwGetKey(mainWindow,GLFW_KEY_T))
    {
        int sz = MarchingChunkManager::loadedChunks.size()*MarchingChunk::chunkSize*MarchingChunk::chunkSize*MarchingChunk::chunkSize; //output number of data points stored for this
        std::cout << sz<<std::endl;
    }




}

bool init_shaders()
{
    activeShader = std::shared_ptr<Shader>(new Shader("vert.txt","frag.txt"));

    std::vector<std::string> tempUniforms = {"GrassSampler","RockSampler","V","P","lightPosition_worldSpace"};
    for (int x = 0; x < tempUniforms.size();x++)
    {
        GLuint uniformLocation = glGetUniformLocation(activeShader->ID,tempUniforms[x].c_str());
        activeShader->Uniforms[tempUniforms[x]] = uniformLocation;
        if (uniformLocation == -1)
        {
            std::cout << tempUniforms[x] << std::endl;
            //return false;
        }

    }

    PPShader = std::shared_ptr<Shader>(new Shader("PPvert.txt","PPfrag.txt"));

    std::vector<std::string> PPUniforms = {"renderedTexture","scrSize","time"};
    for (int x = 0; x < PPUniforms.size();x++)
    {
        GLuint uniformLocation = glGetUniformLocation(PPShader->ID,PPUniforms[x].c_str());
        PPShader->Uniforms[PPUniforms[x]] = uniformLocation;
        if (uniformLocation == -1)
        {
            std::cout << PPUniforms[x] << std::endl;
            //return false;
        }

    }
    //glUseProgram(activeShader->ID);
    glFlush();
    return true;
}
glm::mat4 getProjectionMatrix()
{
    return glm::perspective((double)glm::radians(activeCamera->FOV),(double)width/height,0.1,100000.0);
}
}
