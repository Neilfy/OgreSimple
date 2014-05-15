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
			Texture* tex = it->second;
			if(!tex->IsCreated())
			{
				tex->Create();
			}
			return tex;
		}

		return NULL;
	}

	void TextureManager::LoadTexture(const string& picName)
        {
                map<string, Texture*>::iterator it = mTextures.find(picName);
                if (it != mTextures.end())
                {
                        return ;
                }

                Texture *tex = CreateTexture();

                tex->LoadFile(picName);

                mTextures.insert(make_pair(picName, tex));
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


