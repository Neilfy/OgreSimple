#ifndef GLVERTEXINDEXVBO_H
#define GLVERTEXINDEXVBO_H

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

        virtual bool SetVertexData(const VertexData* vertexData);
        virtual bool BindVertexBuffer();
		virtual bool UnBindVertexBuffer();

    protected:
        void releaseVBO();
    };

    class GLIndexVBO : public IndexVBO
    {
    public:
        GLIndexVBO();
        virtual ~GLIndexVBO();

        virtual bool SetIndexData(const IndexData* indexData);
        virtual bool BindIndexBuffer();
		virtual bool UnBindIndexBuffer();

    protected:
        void releaseVBO();
    };
}
#endif // VERTEXINDEXVBO_H
