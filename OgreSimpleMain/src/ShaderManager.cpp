#include "MapShaderManager.h"

#include <utility>
#include "MapRenderer.h"

using std::map;
using std::string;
using std::make_pair;

namespace ME
{
	ShaderManager* ShaderManager::msInstance = 0;

	ShaderManager::ShaderManager(void)
	{
	}

	ShaderManager::~ShaderManager(void)
	{
	}

	ShaderManager* ShaderManager::Instance(void)
	{
		if (0 == msInstance)
		{
			msInstance = new ShaderManager();
		}
		return msInstance;
	}

	void ShaderManager::Destroy(void)
	{
		if (0 != msInstance)
		{
			delete msInstance;
			msInstance = 0;
		}
	}

	SpShader ShaderManager::GetShader(const string& shaderName)
	{
		map<string, SpShader>::iterator it = mShaders.find(shaderName);
		if (it != mShaders.end())
		{
			return it->second;
		}
		else
		{
			return SpShader(reinterpret_cast<Shader*>(0));
		}
	}

	void ShaderManager::AddShader(const std::string& shaderName, SpShader& shader)
	{
		mShaders.insert(make_pair(shaderName, shader));
	}

    bool ShaderManager::CompileAllShaders(Renderer* renderer)
    {
        if (NULL == renderer)
        {
            return false;
        }

        bool compiled = true;
        for (map<string, SpShader>::iterator it = mShaders.begin();
            it != mShaders.end(); ++it)
        {
            if (0 != it->second)
            {
                if (0 != renderer->CompileShader(it->second))
                {
                    compiled = false;
                }
            }
        }

        return compiled;
    }

    void ShaderManager::ReleaseShaders(void)
    {
        for (map<string, SpShader>::iterator it = mShaders.begin();
            it != mShaders.end(); ++it)
        {
            if (0 != it->second)
            {
                it->second->ReleaseHandle();
            }
        }
    }
}
