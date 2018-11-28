#include "Octree.h"
#include <iostream>
int Octree::maxLOD = 8;
bool Octree::doUpdate = false;
int Octree::octreeCount = 0;
float Octree::maxSize = 10000.;
Octree* Octree::mainOctree;
Octree::Octree(/*std::shared_ptr<Octree>n_Parent,*/ int n_LOD, glm::vec3 n_pos)
:LOD(n_LOD)/*,Parent(n_Parent)*/,pos(n_pos)
{
    octreeCount++;
    mySize = getSize(n_LOD);

}

float Octree::getSize(int n_LOD)
{
    return maxSize*std::pow(2.0,-n_LOD);
}

float Octree::splitCondition(int n_LOD)
{
    return maxSize*std::pow(1.7,-n_LOD);
}

void Octree::update(glm::vec3 inPos)

{

    float dist = glm::length(pos+glm::vec3(mySize/2)-inPos);
    if (dist < splitCondition(LOD) && LOD < maxLOD)
    {
        if (!isBranch)
        {
//            std::cout << "SPLITTING"<<std::endl;
            split();
            isNode = false;
            //std::cout << "NOT NODE";
            isBranch = true;
        }
    }
    else
    {
        isBranch = false;
        isNode = true;
//        std::cout << "NODE";
        Children.clear();

    }
    //update children
    for (int x = 0; x < Children.size();x++)
    {
        Children[x]->update(inPos);

    }
    if (!isNode && objectGenerated)
    {
        objectGenerated = false;
        //delete the chunk here
        delete nodeObject;

    }
    if (isNode && !objectGenerated) //anything that is not 0 implies an object
    {
        objectGenerated = true;
        //generate the chunk here
        nodeObject = new MarchingChunk(pos,mySize/(float)MarchingChunk::chunkSize);
    }
    //std::cout << nodeObject->position.x;
    if (isDebug)
    {
//        std::cout << octreeCount << std::endl;
    }

}

void Octree::split()
{

    for (int x = 0; x <= 1;x++)
    {
        for (int y = 0; y <= 1;y++)
        {
            for (int z = 0; z <= 1; z++)
            {
                //std::shared_ptr<Octree> me = std::shared_ptr<Octree>(this);
                //std::shared_ptr<Octree> child = std::shared_ptr<Octree>(new Octree(me,LOD+1,))
                Children.push_back(std::shared_ptr<Octree>(new Octree(LOD+1,pos+glm::vec3(x,y,z)*glm::vec3(mySize/2))));
            }
        }
    }
}

Octree::~Octree()
{
    Children.clear();
    octreeCount--;
    if (objectGenerated)
    {
        objectGenerated = false;
        delete nodeObject;
    }
    //TODO: REMOVE NODE OBJECT

}
