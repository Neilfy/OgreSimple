#include "MaterialManager.h"
#include "Material.h"
#include "ShaderManager.h"
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

	void MaterialManager::initialise()
	{
	    Material * default_mat = create("BaseWhite");
	    Technique* tec = default_mat->createTechnique();
	    tec->SetColorEnabled(true);
	    tec->SetObjectColor(Color::White);

		GpuProgram* program = tec->CreateGpuProgram();
		Shader* vsShader = ShaderManager::getSingleton()->CreateShader("Basic.vert");
		program->mVertexShader = vsShader;
		Shader* fsShader = ShaderManager::getSingleton()->CreateShader("BasicObjectColor.frag");
		program->mFragmentShader = fsShader;
	}

	Material* MaterialManager::create(const std::string& name)
	{
        std::map<std::string, Material*>::iterator it = mMaterials.find(name);
		if (it != mMaterials.end())
		{
			return it->second;
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
