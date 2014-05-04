#ifndef GLTEXTUREMANAGER_H
#define GLTEXTUREMANAGER_H

#include "TextureManager.h"

namespace OgreSimple
{
	class GLTextureManager : public TextureManager
	{
	public:
		GLTextureManager(void);
		virtual ~GLTextureManager(void);

	protected:
		virtual Texture* CreateTexture(void);
	};
}

#endif // GLTEXTUREMANAGER_H
