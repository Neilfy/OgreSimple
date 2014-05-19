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
		float width = 6.0;
		float height = 4.0;
		float ceil[] = {
			-len/2, height, -width/2,
			-len/2, height, width/2,
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
			-len/2, 0, width/2, width/0.6, 0,
			len/2, 0, -width/2, 0, len/0.6,
			len/2, 0, width/2, width/0.6, len/0.6
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
			std::string texName = "Common/floor.jpg";
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

		//wall front
		float wall_front[] = {
			-len/2, height, -width/2,
			-len/2, 0, -width/2,
			len/2, height, -width/2,
		    len/2, 0, -width/2
		};

		sub = mMesh->createSubMesh();
		size_byte = sizeof(wall_front);
		sub->createVertexData(FVF_POSITION, 4, false);
		sub->addVertices((uint8*)wall_front, size_byte);
		sub->mOperationType = RenderOperation::OT_TRIANGLE_STRIP;
		Material * mat_blue = MaterialManager::getSingleton()->create("BaseBlue");
	    Technique* tec_blue = mat_blue->createTechnique();
	    tec_blue->SetColorEnabled(true);
	    tec_blue->SetObjectColor(Color::Blue);
		sub->setMaterialName("BaseBlue");

		//wall back
		float wall_back[] = {
			-len/2, height, width/2,
			-len/2, 0, width/2,
			len/2, height, width/2,
			len/2, 0, width/2
		};

		sub = mMesh->createSubMesh();
		size_byte = sizeof(wall_back);
		sub->createVertexData(FVF_POSITION, 4, false);
		sub->addVertices((uint8*)wall_back, size_byte);
		sub->mOperationType = RenderOperation::OT_TRIANGLE_STRIP;
		sub->setMaterialName("BaseBlue");

		//wall left
		float wall_left[] = {
			-len/2, height, width/2,
			-len/2, 0, width/2,
			-len/2, height, -width/2,
			-len/2, 0, -width/2
		};

		sub = mMesh->createSubMesh();
		size_byte = sizeof(wall_left);
		sub->createVertexData(FVF_POSITION, 4, false);
		sub->addVertices((uint8*)wall_left, size_byte);
		sub->mOperationType = RenderOperation::OT_TRIANGLE_STRIP;
		sub->setMaterialName("BaseWhite");

		//wall right
		float wall_right[] = {
			len/2, height, width/2,
			len/2, 0, width/2,
			len/2, height, -width/2,
			len/2, 0, -width/2
		};
		sub = mMesh->createSubMesh();
		size_byte = sizeof(wall_right);
		sub->createVertexData(FVF_POSITION, 4, false);
		sub->addVertices((uint8*)wall_right, size_byte);
		sub->mOperationType = RenderOperation::OT_TRIANGLE_STRIP;
		sub->setMaterialName("BaseWhite");
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
