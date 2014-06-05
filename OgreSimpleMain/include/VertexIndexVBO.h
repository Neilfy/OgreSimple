#ifndef VERTEXINDEXVBO_H
#define VERTEXINDEXVBO_H

#include "VertexIndexData.h"
namespace OgreSimple
{
    class VertexVBO
    {
    public:
        VertexVBO(){};
        virtual ~VertexVBO(){};

        virtual bool UpdateVBO() = 0;
        virtual bool BindVertexBuffer(const VertexData* vertexData) = 0;
		virtual bool UnBindVertexBuffer() = 0;

    protected:
        virtual void releaseVBO() = 0;
    };

    class IndexVBO
    {
    public:
        IndexVBO(){};
        virtual ~IndexVBO(){};

        virtual bool UpdateVBO() = 0;
        virtual bool BindIndexBuffer(const IndexData* indexData) = 0;
		virtual bool UnBindIndexBuffer() = 0;

    protected:
        virtual void releaseVBO() = 0;
    };
}
#endif // VERTEXINDEXVBO_H
