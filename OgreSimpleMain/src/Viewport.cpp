#include "Viewport.h"

namespace OgreSimple
{
	Viewport::Viewport(uint32 left, uint32 top, uint32 width, uint32 height,
			Color backColor, float minZ, float maxZ)
		: mLeft(left)
		, mTop(top)
		, mWidth(width)
		, mHeight(height)
		, mBackColor(backColor)
		, mMinZ(minZ)
		, mMaxZ(maxZ)
	{}
}
