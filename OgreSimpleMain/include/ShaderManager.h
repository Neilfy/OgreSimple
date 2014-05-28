#ifndef CXX_MAP_SHADERMANAGER_H
#define CXX_MAP_SHADERMANAGER_H

#include <boost/noncopyable.hpp>
#include <map>
#include <string>

#include "MapShader.h"

namespace ME
{
    class Renderer;

	class ShaderManager : private boost::noncopyable
	{
	public:
		ShaderManager(void);
		~ShaderManager(void);

	public:
		static ShaderManager* Instance(void);
		static void Destroy(void);

	public:
		SpShader GetShader(const std::string& shaderName);
		void AddShader(const std::string& shaderName, SpShader& shader);

        bool CompileAllShaders(Renderer* renderer);
        void ReleaseShaders(void);

	protected:
		std::map<std::string, SpShader>	mShaders;

	private:
		static	ShaderManager* msInstance;
	};
}

#endif // CXX_MAP_SHADERMANAGER_H
