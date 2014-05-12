#include "SubMesh.h"
#include "Mesh.h"
namespace OgreSimple {
    //-----------------------------------------------------------------------
	SubMesh::SubMesh()
		: mOperationType(RenderOperation::OT_TRIANGLE_LIST)
		, mVertexData(NULL)
        , mIndexData(NULL)

    {
    }
    //-----------------------------------------------------------------------
    SubMesh::~SubMesh()
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

	void SubMesh::getRenderOperation(RenderOperation& ro)
	{
		ro.mVertexData = mVertexData;
		ro.mIndexData = mIndexData;
		ro.mOperationType = mOperationType;

	}

	//-----------------------------------------------------------------------
	const std::string& SubMesh::getMaterialName(void) const
	{
		return mMaterialName;
	}
	//-----------------------------------------------------------------------
	void SubMesh::setMaterialName( const std::string& name)
	{
		mMaterialName = name;
	}

	void SubMesh::createVertexData(int vertexType, int numVertices, bool bUseVBO)
    {
        if(mVertexData)
        {
           delete mVertexData;
           mVertexData = NULL;
        }
        mVertexData = new VertexData(vertexType, numVertices, bUseVBO);
    }

    void SubMesh::addVertices(uint8* buf, int size)
    {
        if(mVertexData)
        {
            mVertexData->writeBuffer(buf, size);
        }
    }

    void SubMesh::createIndexData(IndexType type, int numIndexes, bool bUseVBO)
    {
        if(mIndexData)
        {
            delete mIndexData;
            mIndexData = NULL;
        }
        mIndexData = new IndexData(type, numIndexes, bUseVBO);
    }

    void SubMesh::addIndexes(uint8* buf, int size)
    {
        if(mIndexData)
        {
            mIndexData->writeBuffer(buf, size);
        }
    }

}

