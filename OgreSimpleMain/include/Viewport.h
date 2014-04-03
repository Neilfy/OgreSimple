#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Color.h"

namespace OgreSimple
{
    class Viewport
    {
    public:
        Viewport(uint32 left, uint32 top, uint32 width, uint32 height,
            Color backColor = Color::Black,
            float minZ = 0.0f,
            float maxZ = 1.0f);

        ~Viewport(void){};

    public:
        void SetSize(uint32 left, uint32 top, uint32 width, uint32 height)
        {
            mLeft = left;
            mTop = top;
            mWidth = width;
            mHeight = height;
        }

        void SetBackColor(const Color& backColor)
        {
            mBackColor = backColor;
        }

        void SetZRange(float minZ, float maxZ)
        {
            mMinZ = minZ;
            mMaxZ = maxZ;
        }

        uint32 GetLeft(void) const
        {
            return mLeft;
        }
        uint32 GetTop(void) const
        {
            return mTop;
        }
        uint32 GetWidth(void) const
        {
            return mWidth;
        }
        uint32 GetHeight(void) const
        {
            return mHeight;
        }
        Color GetBackColor(void) const
        {
            return mBackColor;
        }
        float GetMinZValue(void) const
        {
            return mMinZ;
        }
        float GetMaxZValue(void) const
        {
            return mMaxZ;
        }

    protected:
        uint32    mLeft;
        uint32    mTop;
        uint32    mWidth;
        uint32    mHeight;

        Color    mBackColor;

        float    mMinZ;
        float    mMaxZ;
    };
}

#endif // CXX_MAP_VIEWPORT_H
