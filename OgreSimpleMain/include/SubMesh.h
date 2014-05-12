
#ifndef __SubMesh_H_
#define __SubMesh_H_

#include "VertexIndexData.h"
#include "RenderOperation.h"
#include <string>
namespace OgreSimple {

    class Mesh;
	class SubMesh
    {
	protected:
		std::string mMaterialName;


    public:
        SubMesh();
        ~SubMesh();

		Mesh* parent;
		RenderOperation::OperationType mOperationType;
		VertexData *mVertexData;
		/// Face index data
		IndexData *mIndexData;

		void getRenderOperation(RenderOperation& ro);
		void setMaterialName( const std::string& name );
		const std::string& getMaterialName() const;

        void createVertexData(int vertexType, int numVertices, bool bUseVBO);
        void addVertices(uint8* buf, int size);

        void createIndexData(IndexType type, int numIndexes, bool bUseVBO);
        void addIndexes(uint8* buf, int size);

    };

} // namespace

#endif

