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

	void GLRenderSystem::render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		//glTranslatef(0.0f,0.0f,6.0f);

		glBegin(GL_TRIANGLES);							// 绘制三角形

		glVertex3f( 0.0f, 1.0f, 0.0f);					// 上顶点

		glVertex3f(-1.0f,-1.0f, 0.0f);					// 左下

		glVertex3f( 1.0f,-1.0f, 0.0f);					// 右下

		glEnd();

	}
}

