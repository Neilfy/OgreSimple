#ifndef GLRENDERSYSTEM_H
#define GLRENDERSYSTEM_H

#include "RenderSystem.h"
#include "GpuProgram.h"
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
		Matrix4 mWorldMatrix;
		Matrix4 mViewMatrix;
		GpuProgram* mGpuProgram;

    private:
        void initialiseContext();
    public:
        GLRenderSystem(void);
        virtual ~GLRenderSystem(void);

        void initialise();
        void render(RenderOperation* ro);
        void clearFrameBuffer(/*unsigned int buffers,
            const ColourValue& colour = ColourValue::Black,
            float depth = 1.0f, unsigned short stencil = 0*/);
        void setViewport(const Viewport& vp);

        void setWorldMatrix(const Matrix4& mat);
        void setViewMatrix(const Matrix4& mat);
        void setProjectionMatrix(const Matrix4& mat);

        void setMaterial(Material* mat);
        void setTextureUnit(TextureUnit* texUnit);

        void enableLighting(bool enable);
        void enableTexture(bool enable);
		void DeleteShader(uint32 shader);
		void DeleteProgram(uint32 program);
		bool ActiveProgram(GpuProgram* program);
		bool CompileGpuProgram(GpuProgram* program);
		uint32 CompileShader(Shader* shader);
    };
}

#endif


