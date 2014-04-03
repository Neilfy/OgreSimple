#include "Color.h"

#include "NMath.h"

namespace OgreSimple
{
    const Color Color::ZERO = Color(0);
    const Color Color::Black = Color(0xFF000000);
    const Color Color::White = Color(0xFFFFFFFF);
    const Color Color::Red = Color(0xFF0000FF);
    const Color Color::Green = Color(0xFF00FF00);
    const Color Color::Blue = Color(0xFFFF0000);

    const Color Color::Yellow = Color(0xFF00FFFF);
    const Color Color::Purple = Color(0xFF800080);
    const Color Color::Pink = Color(0xFFCBC0FF);

    Color::Color(uint32 color)
        : mRawValue(color)
    {}

    Color::Color(uint8 r, uint8 g, uint8 b, uint8 a)
        : mRawValue((a << 24) | (b << 16) | (g << 8) | r)
    {}

    Color::Color(float r, float g, float b, float a)
        : mRawValue(
            (uint8(((a > 1.0f) ? 1.0f : a) * 0xFF) << 24)
            | (uint8(((b > 1.0f) ? 1.0f : b) * 0xFF) << 16)
            | (uint8(((g > 1.0f) ? 1.0f : g) * 0xFF) << 8)
            | uint8(((r > 1.0f) ? 1.0f : r) * 0xFF)
        )
    {}

    Color::Color(const Vector4& color)
        : mRawValue(
            (uint8(((color.w > 1.0f) ? 1.0f : color.w) * 0xFF) << 24)
            | (uint8(((color.z > 1.0f) ? 1.0f : color.z) * 0xFF) << 16)
            | (uint8(((color.y > 1.0f) ? 1.0f : color.y) * 0xFF) << 8)
            | uint8(((color.x > 1.0f) ? 1.0f : color.x) * 0xFF)
        )
    {}

    Color& Color::operator=(const Color& rhs)
    {
        if (&rhs != this)
        {
            this->mRawValue = rhs.mRawValue;
        }

        return *this;
    }
    Color& Color::operator=(const Vector4& rhs)
    {
        *this = Color(rhs);
        return *this;
    }


    float Color::GetRf(void) const
    {
        return (mRawValue & 0xFF) / 255.0f;
    }

    float Color::GetGf(void) const
    {
        return ((mRawValue >> 8) & 0xFF) / 255.0f;
    }

    float Color::GetBf(void) const
    {
        return ((mRawValue >> 16) & 0xFF) / 255.0f;
    }

    float Color::GetAf(void) const
    {
        return ((mRawValue >> 24) & 0xFF) / 255.0f;
    }

    Vector4 Color::ToVector4(void) const
    {
        return Vector4((mRawValue & 0xFF) / 255.0f,
            ((mRawValue >> 8) & 0xFF) / 255.0f,
            ((mRawValue >> 16) & 0xFF) / 255.0f,
            ((mRawValue >> 24) & 0xFF) / 255.0f);
    }
}
