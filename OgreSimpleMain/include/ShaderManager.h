#ifndef CXX_SHADERMANAGER_H
#define CXX_SHADERMANAGER_H

#include <map>
#include <string>

#include "Shader.h"

namespace OgreSimple
{
    class RendererSystem;

	class ShaderManager
	{
	public:
		ShaderManager(void);
		~ShaderManager(void);

	public:
		static ShaderManager* getSingleton(void);

	public:
		Shader* GetShader(const std::string& shaderName);
		Shader* CreateShader(const std::string& shaderName);

        bool CompileAllShaders(RenderSystem* renderer);
        void ReleaseShaders(void);

	protected:
		std::map<std::string, Shader*>	mShaders;

	private:
		static	ShaderManager* mSingleton;
	};
}

#endif // CXX_SHADERMANAGER_H
