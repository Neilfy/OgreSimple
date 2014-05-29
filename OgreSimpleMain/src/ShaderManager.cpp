#include "ShaderManager.h"

#include <utility>
#include "RenderSystem.h"

using std::map;
using std::string;
using std::make_pair;

namespace OgreSimple
{
    string BASIC_VS =
    "void main()\n"
    "{\n"
    "   gl_FrontColor = gl_Color;\n"
    "   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
    "   gl_Position = ftransform();\n"
    "}\n";

    string BASIC_TEXTURE_FS =
    "uniform sampler2D Texture0;"
    "void main()\n"
    "{\n"
    "   gl_FragColor = texture2D(Texture0, gl_TexCoord[0].st);"
    "}\n";
	ShaderManager* ShaderManager::mSingleton = 0;

	ShaderManager::ShaderManager(void)
	{
		mSingleton = this;
	}

	ShaderManager::~ShaderManager(void)
	{
	    std::map<std::string, Shader*>::iterator it, it_end;
		it_end = mShaders.end();
		for ( it = mShaders.begin(); it != it_end; ++it )
		{
			delete it->second;
		}
		mShaders.clear();
		mSingleton = 0;
	}

	ShaderManager* ShaderManager::getSingleton(void)
	{
		return mSingleton;
	}

	Shader* ShaderManager::GetShader(const string& shaderName)
	{
		map<string, Shader*>::iterator it = mShaders.find(shaderName);
		if (it != mShaders.end())
		{
			return it->second;
		}
		else
		{
			return NULL;
		}
	}

	Shader* ShaderManager::CreateShader(const std::string& shaderName)
	{
	    map<string, Shader*>::iterator it = mShaders.find(shaderName);
		if (it != mShaders.end())
		{
			return it->second;
		}

		Shader* shader = new Shader();
		if(shaderName == "Basic.vert")
        {
            shader->SetShaderSource(BASIC_VS);
            shader->SetShaderType(Shader::ST_VERTEX);
        }else if(shaderName == "BasicTexture.frag")
        {
            shader->SetShaderSource(BASIC_TEXTURE_FS);
            shader->SetShaderType(Shader::ST_FRAGMENT);
        }
		mShaders.insert(make_pair(shaderName, shader));
		return shader;
	}

    bool ShaderManager::CompileAllShaders(RenderSystem* renderer)
    {
        //TODO
    }

    void ShaderManager::ReleaseShaders(void)
    {
        for (map<string, Shader*>::iterator it = mShaders.begin();
            it != mShaders.end(); ++it)
        {
            if (0 != it->second)
            {
                it->second->ReleaseHandle();
            }
        }
    }
}
