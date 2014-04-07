#ifndef GLHARDWAREMANAGER_H
#define GLHARDWAREMANAGER_H

#include "HardwareManager.h"
#include "GLVertexIndexVBO.h"
namespace OgreSimple
{
    class GLHardwareManager : public HardwareManager
    {
    public:
        GLHardwareManager(){};
        virtual ~GLHardwareManager

        GLVertexVBO* creatVertexVBO();

        GLIndexVBO* creatIndexVBO();
    };
}
#endif // GLHARDWAREMANAGER_H
