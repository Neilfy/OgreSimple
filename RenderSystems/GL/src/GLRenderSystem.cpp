#include <GL/gl.h>
#include "GLRenderSystem.h"
#include "Viewport.h"

namespace OgreSimple
{
    GLRenderSystem::GLRenderSystem(void)
    {
        mGLInitialized = false;
        mViewport = NULL;
    }

    GLRenderSystem::~GLRenderSystem(void)
    {
        
    }
    
    void GLRenderSystem::initialise()
    {
        
    }
    
    void GLRenderSystem::setViewport(const Viewport& vp)
    {
        glViewport(vp.GetLeft(), vp.GetTop(), vp.GetWidth(), vp.GetHeight());

    }

    void GLRenderSystem::setWorldMatrix(const Matrix4& mat)
    {
        glMatrixMode(GL_MODELVIEW);
        Matrix4 worldmat = mat.GetTranspose();
        glLoadMatrixf(worldmat.GetRawPointer());    
    }

    void GLRenderSystem::setViewMatrix(const Matrix4& mat)
    {
        glMatrixMode(GL_MODELVIEW);
        Matrix4 viewmat = mat.GetTranspose();
        glLoadMatrixf(viewmat.GetRawPointer());
    }

    void GLRenderSystem::setProjectionMatrix(const Matrix4& mat)
    {
        glMatrixMode(GL_PROJECTION);
        Matrix4 promat = mat.GetTranspose();
        glLoadMatrixf(promat.GetRawPointer());
    }

    void GLRenderSystem::render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBegin(GL_TRIANGLES);                            // 绘制三角形

        glVertex3f( 0.0f, 1.0f, 0.0f);                    // 上顶点

        glVertex3f(-1.0f,-1.0f, 0.0f);                    // 左下

        glVertex3f( 1.0f,-1.0f, 0.0f);                    // 右下

        glEnd();

        glFlush();
    }
}

