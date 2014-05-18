#include "MovableObject.h"
#include "RenderOperation.h"
#include "RenderSystem.h"
#include "MaterialManager.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshManager.h"
#include <algorithm>

namespace OgreSimple
{
    MovableObject::MovableObject()
	: mPosition(0, 0, 0)
	, mScale(1.0, 1.0, 1.0)
	, mIsTransformNeedUpdate(true)
	, mMesh(NULL)
    {
    }

    MovableObject::~MovableObject()
    {

    }

    void MovableObject::Make()
    {
		mMesh = MeshManager::getSingleton()->createManual("house");
		float len = 13.0;
		float width = 10.0;
		float height = 4.0;
		float ceil[] = {
			-len/2, height, -width/2,
			-len/2, height, width,
			len/2, height, -width/2,
			len/2, height, width/2
		};
		SubMesh *sub = mMesh->createSubMesh();
		int size_byte = sizeof(ceil);
		sub->createVertexData(FVF_POSITION, 4, false);
		sub->addVertices((uint8*)ceil, size_byte);
		sub->mOperationType = RenderOperation::OT_TRIANGLE_STRIP;
		sub->setMaterialName("BaseWhite");

		//floor
		float floor[] = {
			-len/2, 0, -width/2, 0, 0,
			-len/2, 0, width, 0, 1.0,
			len/2, 0, -width/2, 1.0, 0,
			len/2, 0, width/2, 1.0, 1.0
		};

		sub = mMesh->createSubMesh();
		size_byte = sizeof(floor);
		sub->createVertexData(FVF_POSITION | FVF_UV, 4, false);
		sub->addVertices((uint8*)floor, size_byte);
		sub->mOperationType = RenderOperation::OT_TRIANGLE_STRIP;


		Material *mat_floor = MaterialManager::getSingleton()->GetByName("floor");
		if(!mat_floor)
		{
			mat_floor = MaterialManager::getSingleton()->create("floor");
			Technique* tec = mat_floor->createTechnique();
			std::string texName = "Models/tmp/back.jpg";
			size_t pos = texName.find_last_of(".");
			std::string ext = texName.substr(pos+1);
			std::transform(ext.begin(),ext.end(),ext.begin(),::tolower);

			if(ext == "jpg")
			{
				TextureUnit* texUnit = tec->CreateTextureUnit();
				texUnit->SetPicName(texName);
				texUnit->LoadTexture();
			}
		}
		sub->setMaterialName("floor");
    }

    void MovableObject::render(RenderSystem* renderer)
    {
		Matrix4 transform = getTransform();
		renderer->setWorldMatrix(transform);
        uint16 num_submesh = mMesh->getNumSubMeshes();
        for(int i=0; i < num_submesh; ++i)
        {
            SubMesh* submesh = mMesh->getSubMesh(i);

            std::string mat_name = submesh->getMaterialName();
            Material *mat = MaterialManager::getSingleton()->GetByName(mat_name);
            if(mat)
            {
                renderer->setMaterial(mat);
            }
            RenderOperation ro;
            submesh->getRenderOperation(ro);
            renderer->render(&ro);
        }
    }

    void MovableObject::setPosition(Vector3& pos)
    {
        mPosition = pos;
	mIsTransformNeedUpdate = true;
    }

    void MovableObject::setScale(Vector3& scale)
    {
        mScale = scale;
	mIsTransformNeedUpdate = true;
    }

    Matrix4& MovableObject::getTransform()
    {
		if(mIsTransformNeedUpdate)
		{
			mTransform = Matrix4::Identity;
			mTransform = mTransform.Translation(mPosition);
			mTransform *= mTransform.Scaling(mScale);
			mIsTransformNeedUpdate = false;
		}
		return mTransform;
    }

}
