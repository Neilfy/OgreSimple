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

        virtual bool SetBufferData(const VertexData* vertexData);
        virtual bool BindVertexBuffer();
		virtual bool UnBindVertexBuffer();

    protected:
        void releaseVBO();

    private:
        GLuint mBufferID;
    };

    class GLIndexVBO : public IndexVBO
    {
    public:
        GLIndexVBO();
        virtual ~GLIndexVBO();

        virtual bool SetBufferData(const IndexData* indexData);
        virtual bool BindIndexBuffer();
		virtual bool UnBindIndexBuffer();

    protected:
        void releaseVBO();

    private:
        GLuint mBufferID;
    };
}
#endif // VERTEXINDEXVBO_H
