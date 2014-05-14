#include "MovableObject.h"
#include "RenderOperation.h"
#include "RenderSystem.h"
#include "MaterialManager.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshManager.h"
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
