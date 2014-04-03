#ifndef OGRERENDERSYSTEM_H
#define OGRERENDERSYSTEM_H

#include "NMath.h"
#include "Color.h"
#include "Viewport.h"
#include<string>
namespace OgreSimple
{
    class Viewport;
    class RenderSystem
    {
    public:
        RenderSystem();
        virtual ~RenderSystem();
    
    public:
        virtual void initialise();
        virtual void render();

        virtual void setViewport(const Viewport& vp) = 0;
        virtual void setWorldMatrix(const Matrix4& mat) = 0;
        virtual void setViewMatrix(const Matrix4& mat) = 0;
        virtual void setProjectionMatrix(const Matrix4& mat) = 0;
    };
}
#endif
