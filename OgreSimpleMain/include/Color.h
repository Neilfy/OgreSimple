#ifndef COLOR_H
#define COLOR_H

#include "OgreSimpleTypes.h"
namespace OgreSimple
{
	class Vector4;

	class Color
	{
	public:
		static const Color ZERO;
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;

        static const Color Yellow;
        static const Color Purple;
        static const Color Pink;

	public:
		explicit Color(uint32 color = 0xFFFFFFFF);
		Color(uint8 r, uint8 g, uint8 b, uint8 a = 0xFF);
		Color(float r, float g, float b, float a = 1.0f);
		explicit Color(const Vector4& color);

		~Color(void){};

	public:
		Color& operator=(const Color& rhs);
		Color& operator=(const Vector4& rhs);

	public:
		// dwordValue's format: 0xAABBGGRR
		void FromDWORD(uint32 dwordValue)
		{
			mRawValue = dwordValue;
		}

        // dwValue's format: 0xAARRGGBB
        // alpha value
        void FromARGB(uint32 dwValue)
		{
            mRawValue = ((~dwValue) & 0xFF000000) | (dwValue & 0x0000FF00) | ((dwValue & 0xFF)<< 16) | ((dwValue & 0xFF0000)>>16);
		}

		void FromVector4(const Vector4& v)
		{
			*this = Color(v);
		}

		float GetRf(void) const;
		float GetGf(void) const;
		float GetBf(void) const;
		float GetAf(void) const;
		uint32 ToDWORD(void) const
		{
			return mRawValue;
		}

		Vector4 ToVector4(void) const;

	protected:
		uint32	mRawValue;
	};
}

#endif // CXX_MAP_COLOR_H
