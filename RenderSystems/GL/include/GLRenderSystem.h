#ifndef GLRENDERSYSTEM_H
#define GLRENDERSYSTEM_H

#include "RenderSystem.h"
namespace OgreSimple
{
    class GLRenderSystem :
        public RenderSystem
    {
    private:
        bool mGLInitialized;
        
        Viewport* mViewport;

    private:
        void initialiseContext();
    public:
        GLRenderSystem(void);
        virtual ~GLRenderSystem(void);

        void initialise();
        void render();
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
    };
}

#endif


