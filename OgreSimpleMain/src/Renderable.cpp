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


    void Renderable::addIndexes(uint8* buf, int indexType, int numIndexes)
    {
        //TODO
    }
}
