#ifndef TEXTUREUNIT_H
#define TEXTUREUNIT_H

#include "Texture.h"

namespace OgreSimple
{
	class TextureUnit
	{
	public:
		TextureUnit(void);
		~TextureUnit(void);

	public:
        std::string GetPicName(void) const
		{
			return mPicName;
		}

		Texture* GetTexture();

		void SetPicName(const std::string& picName)
		{
			mPicName = picName;
		}

	protected:
		std::string	mPicName;
		Texture	*mTexture;
	};

}

#endif // TEXTUREUNIT_H
