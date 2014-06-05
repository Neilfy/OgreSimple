#include "GLVertexIndexVBO.h"
namespace OgreSimple
{
    GLVertexVBO::GLVertexVBO():
        mBufferID(0)
    {

    }

    GLVertexVBO::~GLVertexVBO()
    {
        releaseVBO();
    }

	bool GLVertexVBO::BindVertexBuffer(const VertexData* vertexData)
    {
		if(mNeedUpdate)
		{
			releaseVBO();
			int size = vertexData->getBufferSize();
			const GLvoid* pBuffer = vertexData->getBuffer();
			glGenBuffersARB(1, &mBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
			glBufferData(GL_ARRAY_BUFFER, size, pBuffer, GL_STATIC_DRAW);

			mNeedUpdate = false;
		}

        if(mBufferID != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
            return true;
        }
        return false;
    }

    bool GLVertexVBO::UnBindVertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return true;
    }

    void GLVertexVBO::releaseVBO()
    {
        if(mBufferID != 0)
        {
            UnBindVertexBuffer();
            glDeleteBuffers(1, &mBufferID);
            mBufferID = 0;
        }
    }

    //==========================================================

    GLIndexVBO::GLIndexVBO():
        mBufferID(0)
    {

    }

    GLIndexVBO::~GLIndexVBO()
    {
        releaseVBO();
    }

    bool GLIndexVBO::BindIndexBuffer(const IndexData* indexData)
    {
		if(mNeedUpdate)
		{
			releaseVBO();
			int size = indexData->getBufferSize();
			const GLvoid* pBuffer = indexData->getBuffer();
			glGenBuffersARB(1, &mBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pBuffer, GL_STATIC_DRAW);

			mNeedUpdate = false;
		}

        if(mBufferID != 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
            return true;
        }
        return false;
    }
    bool GLIndexVBO::UnBindIndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return true;
    }

    void GLIndexVBO::releaseVBO()
    {
        if(mBufferID != 0)
        {
            UnBindIndexBuffer();
            glDeleteBuffers(1, &mBufferID);
            mBufferID = 0;
        }
    }
}
