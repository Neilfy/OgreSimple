#include "Frustum.h"

//#include "MapAABB.h"

namespace OgreSimple
{
	Frustum::Frustum(void)
        : mNear(0.1f)
        , mFar(100.0f)
        , mWidth(1.0f)
        , mHeight(1.0f)
	{
	}

	Frustum::~Frustum(void)
	{
	}

	void Frustum::Update(const Matrix4& cMat)
	{
		
	}
}
