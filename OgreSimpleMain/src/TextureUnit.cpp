#include "TextureUnit.h"
#include "TextureManager.h"
namespace OgreSimple
{
	TextureUnit::TextureUnit(void)
		: mTexture(NULL)
	{
	}

	TextureUnit::~TextureUnit(void)
	{
	}

	Texture* TextureUnit::GetTexture(void)
	{
		if (mTexture)
		{
			return mTexture;
		}

		// get from texture manager
		TextureManager* texMgr = TextureManager::getSingleton();
		if(texMgr)
        {
            mTexture = texMgr->GetTexture(this->mPicName);
        }

		return mTexture;
	}

}
