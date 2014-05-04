#include "GLTextureManager.h"

#include "GLTexture.h"

namespace OgreSimple
{
	GLTextureManager::GLTextureManager(void)
	{

	}
	GLTextureManager::~GLTextureManager(void)
	{
	}

	Texture* GLTextureManager::CreateTexture(void)
	{
		return new GLTexture();
	}
}


