#include "Texture.h"
#include "string.h"
#include "ImageLoader/CJPGLoader.h"
#include "OgreSimpleRoot.h"
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
namespace OgreSimple
{
	Texture::Texture(void)
        : mWidth(0)
        , mHeight(0)
        , mPixelType(PT_RGBA)
        , mTexData(NULL)
	, mIsLoaded(false)
	, mIsCreated(false)
	{
	}

	Texture::~Texture(void)
	{
    }

    void Texture::LoadFile(const std::string& picName)
    {
        string base_path = OgreSimpleRoot::getSingleton()->getResourcePath();
        string file_path = base_path + "/" + picName;

        FILE* pFile = fopen(file_path.c_str(), "rb");
        if(pFile)
		{
		    fseek (pFile , 0 , SEEK_END);
            unsigned int dwSize = ftell (pFile);
            rewind (pFile);

            uint8* stream = new uint8[dwSize];
            fread(stream,1,dwSize,pFile);
            fclose(pFile);

			CJPGLoader* loader = new CJPGLoader();
			loader->LoadFromStream(stream,dwSize);
            int size = loader->GetImageWidth()*loader->GetImageHeight()*3;
            mTexData = new uint8[size];
            memcpy(mTexData,(char*)loader->GetDIB24(),size);

            mWidth = loader->GetImageWidth();
            mHeight = loader->GetImageHeight();
            mPixelType = PT_RGB;
            mIsLoaded = true;
			delete loader;
		}

    }

    void Texture::Create()
    {
        if(mIsLoaded)
        {
            CreateTextureImpl();
            mIsCreated = true;
        }
    }
}
