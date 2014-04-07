#ifndef VERTEXINDEXDATA_H
#define VERTEXINDEXDATA_H

#include "OgreSimpleTypes.h"

namespace OgreSimple
{
    class VertexVBO;
    class VertexData
    {
    public:
        VertexData(int vertexSize, int numVertices, bool bUseVBO);
        ~VertexData();

        void writeBuffer(uint8* buf, int size);
        uint8* getBuffer() const;

        int calVertexTypeSize(int vertexType) const;
        int getVertexType() const;
        int getVerticesCount() const;
    private:
        uint8* mBuffer;
        int mSizeInByte;
        int mNumVertices;
        int mType;
        VertexVBO* mVBO;
    };

    class IndexData
    {
    public:
        enum IndexType
        {
            IT_16BIT,
            IT_32BIT
        };
        IndexData(IndexType type, int numIndexes);
        ~IndexData();

        void writeBuffer(uint8* buf, int size);
        uint8* getBuffer() const;
    private:
        uint8* mBuffer;
        int mSizeInByte;
        int mNumIndexes;
        int mIndexType;
    };
}
#endif
