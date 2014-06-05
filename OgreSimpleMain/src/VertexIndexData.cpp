#include "VertexIndexData.h"
#include "VertexIndexVBO.h"
#include "HardwareManager.h"
#include <assert.h>
#include <string.h>

namespace OgreSimple
{
    VertexData::VertexData(int vertexType, int numVertices, bool bUseVBO):
        mVBO(NULL)
    {
        if(bUseVBO)
        {
            mVBO = HardwareManager::getSingleton()->creatVertexVBO();
        }
        mType = vertexType;
        int size = calVertexTypeSize(vertexType);
        mSizeInByte = size * numVertices;
        mNumVertices = numVertices;
        mBuffer = new uint8[mSizeInByte];
    }
    VertexData::~VertexData()
    {
        if(mBuffer)
        {
            delete[] mBuffer;
        }
        if(mVBO)
        {
            delete mVBO;
        }
    }

    int VertexData::calVertexTypeSize(int vertexType) const
    {
        int vertexSize = 0;

		if (FVF_POSITION & vertexType)
		{
			vertexSize += 12;
		}

		if (FVF_NORMAL & vertexType)
		{
			vertexSize += 12;
		}

		if (FVF_DIFFUSE & vertexType)
		{
			vertexSize += 4;
		}

		if (FVF_UV & vertexType)
		{
			vertexSize += 8;
		}

		return vertexSize;
    }

    void VertexData::writeBuffer(uint8 * buf,int size)
    {
        assert(mSizeInByte >= size);
        memcpy(mBuffer, buf, size);
		if(mVBO)
		{
			mVBO->UpdateVBO();
		}
    }

    uint8* VertexData::getBuffer() const
    {
        return mBuffer;
    }

    void VertexData::BindVBO() const
    {
        if(mVBO)
        {
            mVBO->BindVertexBuffer(this);
        }
    }

    void VertexData::UnbindVBO() const
    {
        if(mVBO)
        {
            mVBO->UnBindVertexBuffer();
        }
    }

    int VertexData::getVertexType() const
    {
        return mType;
    }

    int VertexData::getVerticesCount() const
    {
        return mNumVertices;
    }

    int VertexData::getBufferSize() const
    {
        return mSizeInByte;
    }

    bool VertexData::isUseVBO() const
    {
        return mVBO != NULL;
    }

    //================================================

    IndexData::IndexData(IndexType type, int numIndexes, bool bUseVBO)
        :mVBO(NULL)
    {
        if(bUseVBO)
        {
            mVBO = HardwareManager::getSingleton()->creatIndexVBO();
        }
        mIndexType = type;
        mNumIndexes = numIndexes;

        switch(mIndexType)
        {
        case IT_16BIT:
            mSizeInByte = mNumIndexes * sizeof(unsigned short);
            break;
        case IT_32BIT:
            mSizeInByte = mNumIndexes * sizeof(unsigned int);
        }

        mBuffer = new uint8[mSizeInByte];
    }
    IndexData::~IndexData()
    {
        if(mBuffer)
        {
            delete[] mBuffer;
        }
        if(mVBO)
        {
            delete mVBO;
        }
    }

    void IndexData::writeBuffer(uint8 *buf,int size)
    {
        assert(mSizeInByte >= size);
        memcpy(mBuffer, buf, size);
		if(mVBO)
		{
			mVBO->UpdateVBO();
		}
    }

    uint8* IndexData::getBuffer() const
    {
        return mBuffer;
    }

    void IndexData::BindVBO() const
    {
        if(mVBO)
        {
            mVBO->BindIndexBuffer(this);
        }
    }

    void IndexData::UnbindVBO() const
    {
       if(mVBO)
        {
            mVBO->UnBindIndexBuffer();
        }
    }

    IndexType IndexData::getIndexType() const
    {
        return mIndexType;
    }

    int IndexData::getIndexesCount() const
    {
        return mNumIndexes;
    }

    int IndexData::getBufferSize() const
    {
        return mSizeInByte;
    }

    bool IndexData::isUseVBO() const
    {
        return mVBO != NULL;
    }
}
