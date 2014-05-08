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
		virtual void LoadFile(const std::string& picName);
		virtual void Create();

        virtual uint32 GetTexWidth() const { return mWidth; }
        virtual uint32 GetTexHeight() const { return mHeight; }
        virtual PixelType GetPixelType() const { return mPixelType; }
		bool IsLoaded() const
		{
			return mIsLoaded;
		}

		bool IsCreated() const
                {
                        return mIsCreated;
                }

    protected:
        virtual void CreateTextureImpl() = 0;

	protected:
        static const int32  msDefaultAlignment = 4;

	protected:
        uint32      mWidth;
        uint32      mHeight;
        PixelType   mPixelType;
        uint8       *mTexData;
	private:
		bool mIsLoaded;
		bool mIsCreated;
	};

}

#endif // TEXTURE_H
