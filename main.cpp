// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <iostream>
#include "GameWindow.h"
#include "Util.h"
#include "MarchingChunk.h"
#include "MarchingChunkManager.h"
#include "GPUMarchingCubes.h"
#include "Tables.h"
#include "Octree.h"



typedef std::chrono::high_resolution_clock Clock;
int main (void)
{


    if (!GameWindow::init_gl())
    {
        std::cout << "Load Failed" << std::endl;
        return -1;
    }
    GameWindow::init_shaders();
    GameWindow::activeCamera =std::shared_ptr<Camera>( new Camera);


    GPUMarchingCubes::init();

    MarchingChunkManager::genVAO();



    GLuint GrassTexture = Util::loadBMP("grass.bmp",true);
    GLuint GrassTextureID = GameWindow::activeShader->Uniforms["GrassSampler"];

    GLuint RockTexture = Util::loadBMP("rock.bmp",true);
    GLuint RockTextureID = GameWindow::activeShader->Uniforms["RockSampler"];

    GameWindow::init_postProcess();


    Octree::mainOctree = new Octree(0,glm::vec3(0));
    Octree::mainOctree->isDebug = true;



    auto tStart = Clock::now();
    glBindVertexArray(MarchingChunkManager::VAO);
    Octree::mainOctree->update(GameWindow::activeCamera->pos);

    ///BEGIN MAIN LOOP
    do
    {


        if (Octree::doUpdate || true)
        {
            Octree::mainOctree->update(GameWindow::activeCamera->pos);

        }

        glfwPollEvents();
        GameWindow::handleInput();


        glUseProgram(GameWindow::activeShader->ID);

        glBindFramebuffer(GL_FRAMEBUFFER,GameWindow::FrameBuffer);
        glViewport(0,0,GameWindow::width,GameWindow::height);

        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,GrassTexture);
        glUniform1i(GrassTextureID,0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,RockTexture);
        glUniform1i(RockTextureID,1);



        //std::cout << "ASDASD";
        //std::cout << "AA";
        for (auto itr = MarchingChunkManager::loadedChunks.begin(); itr != MarchingChunkManager::loadedChunks.end(); itr++)
        {
            //std::cout << "DRAWING" << std::endl;
            (*itr)->draw();
        }


        //now do PP
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glViewport(0,0,GameWindow::width,GameWindow::height);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(GameWindow::PPShader->ID);
        glUniform2f(GameWindow::PPShader->Uniforms["scrSize"],GameWindow::width,GameWindow::height);
        float T = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-tStart).count();
        glUniform1f(GameWindow::PPShader->Uniforms["time"],T);


        glBindVertexArray(GameWindow::quad_VertexArrayID);
        glBindBuffer(GL_ARRAY_BUFFER,GameWindow::quad_vertexbuffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,GameWindow::RenderedTexture);
        glUniform1i(GameWindow::PPShader->Uniforms["renderedTexture"],0);


        glDrawArrays(GL_TRIANGLES,0,6);
        ///todo
        //c.draw();
        //c2.draw();
        glFinish();
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(GameWindow::mainWindow);



    }
    while(glfwGetKey(GameWindow::mainWindow,GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(GameWindow::mainWindow));
    return 0;




}
