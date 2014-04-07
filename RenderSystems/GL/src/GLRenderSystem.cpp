#include <GL/gl.h>
#include "GLRenderSystem.h"
#include "Viewport.h"
#include "RenderOperation.h"

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

    void GLRenderSystem::render(RenderOperation* ro)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderSystem::render(ro);
        const VertexData *vertexData = ro->mVertexData;
        uint8 *buffer = vertexData->getBuffer();
        int vertexType = vertexData->getVertexType();
        int stride = vertexData->calVertexTypeSize(vertexType);
        if (FVF_POSITION & vertexType)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, stride, buffer);
			buffer += 12;
		}
		if (FVF_NORMAL & vertexType)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, stride, buffer);
			buffer += 12;
		}
		if (FVF_DIFFUSE & vertexType)
		{
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_UNSIGNED_BYTE, stride, buffer);
			buffer += 4;
		}
		if (FVF_UV & vertexType)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, stride, buffer);
			buffer += 8;
		}

		GLint primType;

		switch (ro->mOperationType)
		{
		case RenderOperation::OT_POINT_LIST:
			primType = GL_POINTS;
			break;
		case RenderOperation::OT_LINE_LIST:
			primType =  GL_LINES;
			break;
		case RenderOperation::OT_LINE_STRIP:
			primType =  GL_LINE_STRIP;
			break;
		default:
		case RenderOperation::OT_TRIANGLE_LIST:
			primType =  GL_TRIANGLES;
			break;
		case RenderOperation::OT_TRIANGLE_STRIP:
			primType =  GL_TRIANGLE_STRIP;
			break;
		case RenderOperation::OT_TRIANGLE_FAN:
			primType = GL_TRIANGLE_FAN;
			break;
		}

		glDrawArrays(primType, 0, vertexData->getVerticesCount());

        glFlush();
    }
}

