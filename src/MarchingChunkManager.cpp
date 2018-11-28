#include "MarchingChunkManager.h"

namespace MarchingChunkManager
{
    std::vector<MarchingChunk*> loadedChunks;
    GLuint VAO;
    bool genVAO()
    {

        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        return glIsVertexArray(VAO);
    }


}

