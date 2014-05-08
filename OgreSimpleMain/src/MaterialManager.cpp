#include "MaterialManager.h"
#include "Material.h"
namespace OgreSimple
{
    MaterialManager* MaterialManager::mSingleton = 0;
    MaterialManager::MaterialManager()
    {
        mSingleton = this;
	}

	MaterialManager::~MaterialManager()
	{
	    std::map<std::string, Material*>::iterator it, it_end;
		it_end = mMaterials.end();
		for ( it = mMaterials.begin(); it != it_end; ++it )
		{
			delete it->second;
		}
		mMaterials.clear();
		mSingleton = 0;
	}

	MaterialManager* MaterialManager::getSingleton()
	{
		return mSingleton;
	}

	Material* MaterialManager::create(const std::string& name)
	{
        std::map<std::string, Material*>::iterator it = mMaterials.find(name);
		if (it != mMaterials.end())
		{
			return NULL;
		}

		Material* mat = new Material();
		mMaterials.insert(make_pair(name, mat));

		return mat;
	}

        Material* MaterialManager::GetByName(const std::string& name)
        {
                std::map<std::string, Material*>::iterator it = mMaterials.find(name);
                Material* mat = NULL;
                if (it != mMaterials.end())
                {
                        mat = it->second;
                }
		return mat;

        }
}
