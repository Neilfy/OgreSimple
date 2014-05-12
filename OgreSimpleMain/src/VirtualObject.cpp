#include "VirtualObject.h"

#include "RenderSystem.h"
#include "MeshManager.h"
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
        mMesh = MeshManager::getSingleton()->load(mName);
    }

    void VirtualObject::render(RenderSystem* renderer)
    {
        MovableObject::render(renderer);
    }
}
