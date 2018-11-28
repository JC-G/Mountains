#ifndef OCTREE_H
#define OCTREE_H
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "MarchingChunk.h"
class Octree
{
    public:
        static bool doUpdate;
        bool isDebug = false;
        bool objectGenerated = false;
        Octree(/*std::shared_ptr<Octree> n_Parent,*/ int n_LOD,glm::vec3 n_pos);
        static float getSize(int n_LOD);
        static float splitCondition(int n_LOD);
        void update(glm::vec3 inPos);
        void split();
        static Octree* mainOctree;
        ~Octree();
        std::vector<std::shared_ptr<Octree>> Children;
        //std::shared_ptr<Octree> Parent;
        float mySize; //x or y or z
        glm::vec3 pos;
        static int maxLOD;
        static float maxSize;
        static int octreeCount;
        int LOD;
        bool isNode = false;
        bool isBranch = false;
        MarchingChunk* nodeObject;




    protected:

    private:
};

#endif // OCTREE_H
