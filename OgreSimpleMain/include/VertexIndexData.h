#ifndef VERTEXINDEXDATA_H
#define VERTEXINDEXDATA_H

#include "OgreSimpleTypes.h"

namespace OgreSimple
{
    class VertexVBO;
    class IndexVBO;
    class VertexData
    {
    public:
        VertexData(int vertexSize, int numVertices, bool bUseVBO);
        ~VertexData();

        void writeBuffer(uint8* buf, int size);
        uint8* getBuffer() const;

        void BindVBO() const;
        void UnbindVBO() const;

        int calVertexTypeSize(int vertexType) const;
        int getVertexType() const;
        int getVerticesCount() const;
        int getBufferSize() const;
        bool isUseVBO() const;
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

        IndexData(IndexType type, int numIndexes, bool bUseVBO);
        ~IndexData();

        void writeBuffer(uint8* buf, int size);
        uint8* getBuffer() const;

        void BindVBO() const;
        void UnbindVBO() const;

        IndexType getIndexType() const;
        int getIndexesCount() const;
        int getBufferSize() const;
        bool isUseVBO() const;
    private:
        uint8* mBuffer;
        int mSizeInByte;
        int mNumIndexes;
        IndexType mIndexType;
        IndexVBO* mVBO;
    };
}
#endif
