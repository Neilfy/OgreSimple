#ifndef TEXTURE_H
#define TEXTURE_H

#include "OgreSimpleTypes.h"

#include <string>
namespace OgreSimple
{
	class Texture
	{
	public:
		Texture(void);
		virtual ~Texture(void);

	public:
		virtual bool Load(const std::string& picName);

        virtual uint32 GetTexWidth() const { return mWidth; }
        virtual uint32 GetTexHeight() const { return mHeight; }
        virtual PixelType GetPixelType() const { return mPixelType; }
    protected:
        virtual void CreateTextureImpl() = 0;

	protected:
        static const int32  msDefaultAlignment = 4;

	protected:
        uint32      mWidth;
        uint32      mHeight;
        PixelType   mPixelType;
        uint8       *mTexData;
	};

}

#endif // TEXTURE_H
