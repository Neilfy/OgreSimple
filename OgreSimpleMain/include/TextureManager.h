#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>

#include "OgreSimpleTypes.h"
#include "Texture.h"

namespace OgreSimple
{
	class TextureManager
	{
	public:
		TextureManager(void);
		virtual ~TextureManager(void);

		static TextureManager* getSingleton();

	public:
		Texture* GetTexture(const std::string& picName);
		bool DeleteTexture(const std::string& texName);

	protected:
		virtual Texture* CreateTexture(void) = 0;

    private:
        static TextureManager* mSingleton;
        std::map<std::string, Texture*>	mTextures;

	};
}

#endif // TEXTUREMANAGER_H
