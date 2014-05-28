#ifndef OGRERENDERSYSTEM_H
#define OGRERENDERSYSTEM_H

#include "NMath.h"
#include "Color.h"
#include "Viewport.h"
namespace OgreSimple
{
    class Viewport;
    class RenderOperation;
    class Material;
    class RenderSystem
    {
    public:
        RenderSystem();
        virtual ~RenderSystem();

    public:
        virtual void initialise();
        virtual void render(RenderOperation* ro);

        virtual void setViewport(const Viewport& vp) = 0;
        virtual void setWorldMatrix(const Matrix4& mat) = 0;
        virtual void setViewMatrix(const Matrix4& mat) = 0;
        virtual void setProjectionMatrix(const Matrix4& mat) = 0;
		virtual void clearFrameBuffer() = 0;

        virtual void setMaterial(Material* mat) = 0;
		virtual void DeleteShader(uint32 shader) = 0;
		virtual void DeleteProgram(uint32 program) = 0;
    };
}
#endif
