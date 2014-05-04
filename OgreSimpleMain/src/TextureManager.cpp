#include "TextureManager.h"

#include <utility>

using std::string;
using std::map;
using std::make_pair;

namespace OgreSimple
{
    TextureManager* TextureManager::mSingleton = 0;
	TextureManager::TextureManager(void)
	{
        mSingleton = this;
	}
	TextureManager::~TextureManager(void)
	{

	}

	TextureManager* TextureManager::getSingleton()
	{
		return mSingleton;
	}

	Texture* TextureManager::GetTexture(const string& picName)
	{
		map<string, Texture*>::iterator it = mTextures.find(picName);
		if (it != mTextures.end())
		{
			return it->second;
		}

		Texture *tex = CreateTexture();

		if (!tex->Load(picName))
		{
			return NULL;
		}

		mTextures.insert(make_pair(picName, tex));
		return tex;
	}

	bool TextureManager::DeleteTexture(const std::string& texName)
	{
		map<string, Texture*>::iterator it = mTextures.find(texName);
		if (it != mTextures.end())
		{
			mTextures.erase(it);
			return true;
		}

		return false;
	}

}


