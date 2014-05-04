#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "Texture.h"
#include "glew.h"
namespace OgreSimple
{
	class GLTexture : public Texture
	{
	public:
		GLTexture(void);
		virtual ~GLTexture(void);

		GLuint getGLID() const
		{
		    return mTextureID;
        }

    protected:
        virtual void CreateTextureImpl();
    private:
        GLuint mTextureID;

	};
}

#endif // GLTEXTURE_H
