#include "GLTexture.h"

namespace OgreSimple
{
	GLTexture::GLTexture(void)
	{
	}

	GLTexture::~GLTexture(void)
	{

	}

	void GLTexture::CreateTextureImpl()
	{
	    glGenTextures( 1, &mTextureID );
		glBindTexture( GL_TEXTURE_2D, mTextureID );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		GLint pixelType = GL_RGBA;
		GLint alignment = msDefaultAlignment;
		switch (mPixelType)
		{
        case PT_RGB:
            pixelType = GL_RGB;
            alignment = 1;
            break;

        case PT_RGB565:
            pixelType = GL_RGB;
            alignment = 2;
            break;

        case PT_RGBA:
            pixelType = GL_RGBA;
            break;
        case PT_ALPHA:
            pixelType = GL_ALPHA;
            alignment = 1;
            break;
        case PT_RGBA_4444:
            pixelType = GL_RGBA;
            break;

        default:
            return ;
		}
		switch (mPixelType)
		{
		case PT_RGBA:
        case PT_ALPHA:
		case PT_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, pixelType, mWidth, mHeight, 0, pixelType, GL_UNSIGNED_BYTE, mTexData);
			break;
        default:
            return ;
		}
	}
}

