#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include <string>
#include "Technique.h"

namespace OgreSimple
{
	class Material
	{
	public:
		Material(void);
		~Material(void);

	public:
        Technique* createTechnique();
        Technique* getBestTechnique();

	protected:
		std::vector<Technique*>	mTechniques;
		Technique				*mBestTechnique;
	};

}

#endif // MATERIAL_H


