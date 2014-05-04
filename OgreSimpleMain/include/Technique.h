#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <string>

#include "Color.h"
#include "TextureUnit.h"

namespace OgreSimple
{
	class Technique
	{

	public:
		Technique(void);
		~Technique(void);

	public:
		const bool IsColorEnabled(void) const
		{
			return mColorEnabled;
		}
		const Color& GetObjectColor(void) const
		{
			return mObjectColor;
		}

		const Color& GetAmbient(void) const
		{
			return mAmbient;
		}
		const Color& GetDiffuse(void) const
		{
			return mDiffuse;
		}
		const Color& GetSpecular(void) const
		{
			return mSpecular;
		}
		const Color& GetEmission(void) const
		{
			return mEmission;
		}
		float GetShinness(void) const
		{
			return mShininess;
		}

		TextureUnit* GetTextureUnit(void) const
		{
		    return mTextureUnit;
		}


		bool IsLightingEnabled(void)
		{
			return mLightingEnabled;
		}

		bool IsBlendingEnabled(void)
		{
			return mBlendingEnabled;
		}

        BlendFactorType GetSrcBlendFactor()
        {
            return mSrcBlendFactor;
        }

        BlendFactorType GetDstBlendFactor()
        {
            return mDstBlendFactor;
        }

        void SetColorEnabled(bool colorEnabled)
        {
            mColorEnabled = colorEnabled;
        }

        void SetObjectColor(const Color& color)
        {
            mObjectColor = color;
        }

        void SetBlendingEnabled(bool blendingEnabled)
        {
            mBlendingEnabled = blendingEnabled;
        }

        TextureUnit* CreateTextureUnit(void);

	protected:
		bool	mColorEnabled;
		Color	mObjectColor;

		Color	mAmbient;
		Color	mDiffuse;
		Color	mSpecular;
		Color	mEmission;
		float	mShininess;
		bool	mLightingEnabled;

		bool	mBlendingEnabled;
        BlendFactorType mSrcBlendFactor;
        BlendFactorType mDstBlendFactor;

		TextureUnit	*mTextureUnit;
		bool			mTextureEnabled;

	};

}

#endif // TECHNIQUE_H
