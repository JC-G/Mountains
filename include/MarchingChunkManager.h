#ifndef MARCHINGCHUNKMANAGER_H
#define MARCHINGCHUNKMANAGER_H


#include <unordered_map>
#include "MarchingChunk.h"
#include <memory>
//for unorderedmap
namespace std
{
    template<>
    struct hash<glm::vec3>
    {
        size_t operator()(const glm::vec3& vect) const noexcept
        {
            std::hash<decltype(vect.x)> hasher;

            auto hash1 = hasher(vect.x);
            auto hash2 = hasher(vect.y);
            auto hash3 = hasher(vect.z);

            return std::hash<decltype(vect.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
        }
    };
}


namespace MarchingChunkManager
{
    extern std::vector<MarchingChunk*> loadedChunks;
    bool genVAO();
    extern GLuint VAO;


}

#endif // MARCHINGCHUNKMANAGER_H
