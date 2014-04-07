#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "OgreSimpleTypes.h"
#include "VertexIndexData.h"
namespace OgreSimple
{
    class Renderable
    {
    public:
        Renderable();
        virtual ~Renderable();

        void createVertexData(int vertexType, int numVertices, bool bUseVBO);
        void addVertices(uint8* buf, int size);

        void addIndexes(uint8* buf, int indexType, int numIndexes);

        VertexData* getVertexData() const
        {
            return mVertexData;
        } ;

    private:
        VertexData *mVertexData;
        IndexData *mIndexData;
    };
}
#endif
