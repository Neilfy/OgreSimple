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

    void MovableObject::createMaterialWithTexture(std::string texName)
    {
        Material *mat = MaterialManager::getSingleton()->GetByName(texName);
		if(!mat)
		{
			mat = MaterialManager::getSingleton()->create(texName);
			Technique* tec = mat->createTechnique();
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
    }

    void MovableObject::Make()
    {
		mMesh = MeshManager::getSingleton()->createManual("house");
        float halfL = 5;
        float halfW = 5;
        float height = 4;

        for (int i = 0; i < 6; ++i)
		{
			Vector3 ahead;
			Vector3 up, right;

			std::string matName;
			switch(i)
			{
			case 0://BP_FRONT
				ahead = Vector3(0, 0, -halfW);
				up = Vector3(0, height, 0);
				right = Vector3(halfL, 0, 0);
                matName = "SkyBox/front.jpg";
				createMaterialWithTexture( "SkyBox/front.jpg" );
				break;
			case 1://BP_BACK
				ahead = Vector3(0, 0, halfW);
				up = Vector3(0, height, 0);
				right = Vector3(-halfL, 0, 0);
                matName = "SkyBox/back.jpg";
				createMaterialWithTexture( "SkyBox/back.jpg" );
				break;
			case 2://BP_LEFT
				ahead = Vector3(-halfL, 0, 0);
				up = Vector3(0, height, 0);
				right = Vector3(0, 0, -halfW);
                matName = "SkyBox/left.jpg";
				createMaterialWithTexture( "SkyBox/left.jpg" );
				break;
			case 3://BP_RIGHT
				ahead = Vector3(halfL, 0, 0);
				up = Vector3(0, height, 0);
				right = Vector3(0, 0, halfW);
                matName = "SkyBox/right.jpg";
				createMaterialWithTexture( "SkyBox/right.jpg" );
				break;
			case 4://BP_UP
				ahead = Vector3(0, height, 0);
				up = Vector3(0, 0, halfW);
				right = Vector3(halfL, 0, 0);
                matName = "SkyBox/top.jpg";
				createMaterialWithTexture( "SkyBox/top.jpg" );
				break;
			case 5://BP_DOWN
				ahead = Vector3(0, 0, 0);
				up = Vector3(0, 0, -halfW);
				right = Vector3(halfL, 0, 0);
                matName = "Common/floor.jpg";
				createMaterialWithTexture( "Common/floor.jpg" );
				break;
			}


			{
                Vector3 topleft = ahead + up - right;
				Vector3 bottomleft = ahead - up - right;
				Vector3 bottomright = ahead - up + right;
				Vector3 topright = ahead + up + right;

				float pSource[]={
					topleft.x,topleft.y,topleft.z,
					0,1,
					bottomleft.x,bottomleft.y,bottomleft.z,
					0,0,
					bottomright.x,bottomright.y,bottomright.z,
					1,0,
					topright.x,topright.y,topright.z,
					1,1
				};

                short idx[]={
					0,1,2,
					0,2,3
				};

				SubMesh* sm = mMesh->createSubMesh();
                sm->createVertexData(FVF_POSITION | FVF_UV, 4, false);
                sm->addVertices((uint8*)pSource, sizeof(pSource));
                sm->mOperationType = RenderOperation::OT_TRIANGLE_LIST;
                sm->setMaterialName(matName);

                sm->createIndexData(IT_16BIT, 6, false);
                sm->addIndexes((uint8*)idx, sizeof(idx));

			}

		} // for each plane
    }

    void MovableObject::render(RenderSystem* renderer)
    {
		//Matrix4 transform = getTransform();
		//renderer->setWorldMatrix(transform);
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
