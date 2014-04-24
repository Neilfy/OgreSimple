#include "GLHardwareManager.h"
namespace OgreSimple
{
    GLVertexVBO* GLHardwareManager::creatVertexVBO()
    {
        return new GLVertexVBO();
    }

    GLIndexVBO* GLHardwareManager::creatIndexVBO()
    {
        return new GLIndexVBO();
    }
}

