#include "Texture.h"
#include "string.h"
#include "ImageLoader/CJPGLoader.h"
#include <string>
#include <stdio.h>
namespace OgreSimple
{
	Texture::Texture(void)
        : mWidth(0)
        , mHeight(0)
        , mPixelType(PT_RGBA)
        , mTexData(NULL)
	{
	}

	Texture::~Texture(void)
	{
    }

    bool Texture::Load(const std::string& picName)
    {
        std::string path = "E:\\WorkSpace\\OgreSimple\\Sample\\Resources\\Models\\back.jpg";
        FILE* pFile = fopen(path.c_str(), "w");
        fseek (pFile , 0 , SEEK_END);
        unsigned int dwSize = ftell (pFile);
        rewind (pFile);

        uint8* stream = new uint8[dwSize];
        fread(stream,1,dwSize,pFile);


		{
			CJPGLoader* loader = new CJPGLoader();

			loader->LoadFromStream(stream,dwSize);
            int size = loader->GetImageWidth()*loader->GetImageHeight()*3;
            mTexData = new uint8[size];
            memcpy(mTexData,(char*)loader->GetDIB24(),size);

            mWidth = loader->GetImageWidth();
            mHeight = loader->GetImageHeight();
            mPixelType = PT_RGB;

			delete loader;
		}

        CreateTextureImpl();

        return true;
    }
}
