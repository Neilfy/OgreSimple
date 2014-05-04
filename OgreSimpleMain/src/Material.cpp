#include "Material.h"

namespace OgreSimple
{
	Material::Material(void)
	{}

	Material::~Material(void)
	{
	    std::vector<Technique*>::iterator i, iend;
		iend = mTechniques.end();
		for (i = mTechniques.begin(); i != iend; ++i)
		{
			delete *i;
		}
		mTechniques.clear();
	}

	Technique* Material::createTechnique()
	{
	    Technique *t = new Technique();
        mTechniques.push_back(t);
        return t;
	}

	Technique* Material::getBestTechnique()
	{
	    mBestTechnique = mTechniques[0];
	    return mBestTechnique;
	}

}
