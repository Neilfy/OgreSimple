#include "Technique.h"

namespace OgreSimple
	{
	Technique::Technique(void)
		: mColorEnabled(false)
		, mObjectColor(Color::White)
		, mAmbient(0.2f, 0.2f, 0.2f)
		, mDiffuse(1.0f, 1.0f, 1.0f)
		, mSpecular(0.0f, 0.0f, 0.0f)
		, mEmission(0.0f, 0.0f, 0.0f)
		, mShininess(80)
		, mLightingEnabled(false)
		, mBlendingEnabled(false)
		, mSrcBlendFactor(BFT_SRC_ALPHA)
        , mDstBlendFactor(BFT_ONE_MINUS_SRC_ALPHA)
		, mTextureUnit(NULL)
		, mGpuProgram(NULL)
		, mTextureEnabled(false)
	{
	}

	Technique::~Technique(void)
	{
	    if(mTextureUnit)
        {
            delete mTextureUnit;
        }
	}

	TextureUnit* Technique::CreateTextureUnit(void)
	{
	    if(!mTextureUnit)
        {
            mTextureUnit = new TextureUnit();
        }
        return mTextureUnit;
	}

	GpuProgram* Technique::CreateGpuProgram(void)
	{
		if(!mGpuProgram)
		{
			mGpuProgram = new GpuProgram();
		}
		return mGpuProgram;
	}

}
