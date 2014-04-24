#include "Renderable.h"

namespace OgreSimple
{
    Renderable::Renderable()
        :mVertexData(NULL)
        ,mIndexData(NULL)
    {
    }

    Renderable::~Renderable()
    {
        if(mVertexData)
        {
            delete mVertexData;
        }
        if(mIndexData)
        {
            delete mIndexData;
        }
    }

    void Renderable::createVertexData(int vertexType, int numVertices, bool bUseVBO)
    {
        if(mVertexData)
        {
           delete mVertexData;
           mVertexData = NULL;
        }
        mVertexData = new VertexData(vertexType, numVertices, bUseVBO);
    }

    void Renderable::addVertices(uint8* buf, int size)
    {
        if(mVertexData)
        {
            mVertexData->writeBuffer(buf, size);
        }
    }

    void Renderable::createIndexData(IndexType type, int numIndexes, bool bUseVBO)
    {
        if(mIndexData)
        {
            delete mIndexData;
            mIndexData = NULL;
        }
        mIndexData = new IndexData(type, numIndexes, bUseVBO);
    }

    void Renderable::addIndexes(uint8* buf, int size)
    {
        if(mIndexData)
        {
            mIndexData->writeBuffer(buf, size);
        }
    }
}
