#ifndef GLRENDERSYSTEM_H
#define GLRENDERSYSTEM_H

#include "RenderSystem.h"
namespace OgreSimple
{
    class HardwareManager;
    class TextureManager;
    class Material;
    class TextureUnit;
    class GLRenderSystem :
        public RenderSystem
    {
    private:
        bool mGLInitialized;
        HardwareManager *mHardwareManager;
        TextureManager *mTextureManager;
        Viewport* mViewport;

    private:
        void initialiseContext();
    public:
        GLRenderSystem(void);
        virtual ~GLRenderSystem(void);

        void initialise();
        void render(RenderOperation* ro);
        //void _setProjectionMatrix(const Matrix4 &m);
        //void _setViewMatrix(const Matrix4 &m);
        //void _setWorldMatrix( const Matrix4 &m );
        //void clearFrameBuffer(unsigned int buffers,
        //    const ColourValue& colour = ColourValue::Black,
        //    float depth = 1.0f, unsigned short stencil = 0);
        void setViewport(const Viewport& vp);

        void setWorldMatrix(const Matrix4& mat);
        void setViewMatrix(const Matrix4& mat);
        void setProjectionMatrix(const Matrix4& mat);

        void setMaterial(Material* mat);
        void setTextureUnit(TextureUnit* texUnit);

        void enableLighting(bool enable);
        void enableTexture(bool enable);
    };
}

#endif


