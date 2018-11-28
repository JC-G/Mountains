#include "MarchingChunk.h"
#include "GameWindow.h"
#include "DistanceFunctions.h"
#include "Tables.h"
#include <iostream>
#include <GPUMarchingCubes.h>
#include "MarchingChunkManager.h"
#include <chrono>
#include <algorithm>

MarchingChunk::MarchingChunk(glm::vec3 pos,float stride)
    :position(pos)
{
    //auto t1 = Clock::now();

    //std::cout << "Begun" << std::endl;
    glGenBuffers(1,&VertexDataBuffer);
    glGenBuffers(1,&VertexNormalBuffer);
    //apply the marching cubes algorithm
    //create a grid from the positions
    pointCount = GPUMarchingCubes::generateChunk(pos,stride,VertexDataBuffer,VertexNormalBuffer);
    //auto t2 = Clock::now();
//    std::cout << "Took: "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms" << std::endl;
//    std::cout << "PointCount: "<<pointCount << std::endl;
    MarchingChunkManager::loadedChunks.push_back(this);


}


MarchingChunk::~MarchingChunk()
{
    //dtor
    glDeleteBuffers(1,&VertexDataBuffer);
    glDeleteBuffers(1,&VertexNormalBuffer);
    MarchingChunkManager::loadedChunks.erase(std::find(MarchingChunkManager::loadedChunks.begin(),MarchingChunkManager::loadedChunks.end(),this));
}
void MarchingChunk::draw()
{
//    std::cout <<"Matrix Stuff:"<< GameWindow::activeCamera->getViewMatrix()[0][0] << std::endl;
//    std::cout << "MAt2: "<< GameWindow::getProjectionMatrix()[0][0]<<std::endl;
//    std::cout << "ISPROGRAM: " << glIsProgram(GameWindow::activeShader->ID)<<std::endl;
    glUseProgram(GameWindow::activeShader->ID);
    glBindVertexArray(MarchingChunkManager::VAO);
    glm::vec4 lightPos(GameWindow::activeCamera->pos,1);
    glUniform4f(GameWindow::activeShader->Uniforms["lightPosition_worldSpace"],lightPos.x,lightPos.y,lightPos.z,lightPos.w);
    glUniformMatrix4fv(GameWindow::activeShader->Uniforms["V"],1,GL_FALSE,&(GameWindow::activeCamera->getViewMatrix()[0][0]));
    glUniformMatrix4fv(GameWindow::activeShader->Uniforms["P"],1,GL_FALSE,&(GameWindow::getProjectionMatrix()[0][0]));


    glBindBuffer(GL_ARRAY_BUFFER, VertexDataBuffer);


    ///debug
//    GLint buffersz;
//    glGetBufferParameteriv(GL_ARRAY_BUFFER,GL_BUFFER_SIZE,&buffersz);
//    std::cout << "Buffer Size: " << buffersz<< std::endl;
//    glm::vec4 exPoint;
//    glGetBufferSubData(GL_ARRAY_BUFFER,buffersz-(pointCount/2+0)*sizeof(glm::vec4),sizeof(glm::vec4),&exPoint);
//    std::cout << exPoint.x << "|" << exPoint.y << "|"<< exPoint.z << "|" << exPoint.w << std::endl;





    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute
        4,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );


    glBindBuffer(GL_ARRAY_BUFFER,VertexNormalBuffer);


    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)0);
    //std::cout <<"PC: "<< pointCount << std::endl;
    //std::cout << vertexData.size();

    glDrawArrays(
        GL_TRIANGLES,
        0,
        pointCount
    );
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


}
