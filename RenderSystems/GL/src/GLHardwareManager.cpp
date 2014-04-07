#include "GLHardwareManager.h"
namespace OgreSimple
{
    VertexVBO* GLHardwareManager::creatVertexVBO()
    {
        return new GLVertexVBO();
    }

    IndexVBO* GLHardwareManager::creatIndexVBO()
    {
        return new GLIndexVBO();
    }
}

