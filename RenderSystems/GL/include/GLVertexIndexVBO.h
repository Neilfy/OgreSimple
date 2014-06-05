#ifndef GLVERTEXINDEXVBO_H
#define GLVERTEXINDEXVBO_H

#include "glew.h"
#include "VertexIndexVBO.h"
namespace OgreSimple
{
    class VertexData;
    class IndexData;
    class GLVertexVBO : public VertexVBO
    {
    public:
        GLVertexVBO();
        virtual ~GLVertexVBO();

        virtual bool UpdateVBO()
		{
			mNeedUpdate = true;
		};
        virtual bool BindVertexBuffer(const VertexData* vertexData);
		virtual bool UnBindVertexBuffer();

    protected:
        void releaseVBO();

    private:
		bool mNeedUpdate;
        GLuint mBufferID;
    };

    class GLIndexVBO : public IndexVBO
    {
    public:
        GLIndexVBO();
        virtual ~GLIndexVBO();

        virtual bool UpdateVBO()
		{
			mNeedUpdate = true;
		}
        virtual bool BindIndexBuffer(const IndexData* indexData);
		virtual bool UnBindIndexBuffer();

    protected:
        void releaseVBO();

    private:
		bool mNeedUpdate;
        GLuint mBufferID;
    };
}
#endif // VERTEXINDEXVBO_H
