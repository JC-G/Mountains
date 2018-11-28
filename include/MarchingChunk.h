#ifndef MARCHINGCHUNK_H
#define MARCHINGCHUNK_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <vector>
#include <atomic>
#include <mutex>

#include <unordered_map>
#include <limits>
#include <vector>
#include <thread>
#include <mutex>
class MarchingChunk
{
    public:
        std::vector<std::thread> workers;
        std::mutex vectorMutex;
        //float *myGrid;
        static const int chunkSize =16;


        MarchingChunk(glm::vec3 pos,float stride);
        ~MarchingChunk();
        glm::vec3 position;
        std::vector<glm::vec3> vertexData;
        std::vector<glm::vec3> vertexNormals;

        GLuint VertexDataBuffer;
        GLuint VertexNormalBuffer;
        GLuint pointCount=0;

        void draw();

    protected:

    private:
};

#endif // MARCHINGCHUNK_H
