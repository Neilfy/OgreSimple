#include "VirtualObject.h"

#include "RenderSystem.h"
#include "MeshManager.h"
#include <stdio.h>
namespace OgreSimple
{
    VirtualObject::VirtualObject(std::string name)
	:mName(name)
    {
    }

    VirtualObject::~VirtualObject()
    {
    }

    void VirtualObject::Make()
    {
        mMesh = MeshManager::getSingleton()->load(mMeshFile);
    }

    void VirtualObject::render(RenderSystem* renderer)
    {
        printf("====%x\n",renderer);
        MovableObject::render(renderer);
    }


	void VirtualObject::setMeshFile(std::string& path)
	{
		mMeshFile = path;
	}
}
