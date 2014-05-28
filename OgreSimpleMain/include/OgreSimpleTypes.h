#ifndef OGRESIMPLE_TYPES_H
#define OGRESIMPLE_TYPES_H

namespace OgreSimple
{
#ifndef NULL
#define NULL 0
#endif

#define FVF_POSITION 0x00000001
#define FVF_NORMAL 0x00000002
#define FVF_DIFFUSE 0x00000004
#define FVF_UV 0x00000008

    typedef unsigned long long uint64;
    typedef unsigned int uint32;
    typedef unsigned short uint16;
    typedef unsigned char uint8;
    typedef int int32;
    typedef short int16;
    typedef char int8;

    static const float ME_PI = 3.141592654f;

    enum IndexType
    {
        IT_16BIT,
        IT_32BIT
    };

    enum BlendFactorType
	{
		BFT_ZERO,
		BFT_ONE,
		BFT_SRC_COLOR,
		BFT_ONE_MINUS_SRC_COLOR,
		BFT_DST_COLOR,
		BFT_ONE_MINUS_DST_COLOR,
		BFT_SRC_ALPHA,
		BFT_ONE_MINUS_SRC_ALPHA,
		BFT_DST_ALPHA,
		BFT_ONE_MINUS_DST_ALPHA,
		BFT_SRC_ALPHA_SATURATE,
	};

	enum PixelType
	{
		PT_RGBA,
		PT_RGBA_4444,
		PT_RGB,
		PT_ETC1,
		PT_PVRTC4_RGB,
		PT_PVRTC4_RGBA,
		PT_RGB565,
		PT_ALPHA
	};

	enum VertexDataFormat
	{       
		VDF_XYZ     = 1,
		VDF_NORMAL  = 2,
		VDF_DIFFUSE = 4,
		VDF_UV      = 8
	};

	enum UniformType
	{           
		UT_MVPMatrix = 0,
		UT_TEXTURE0,
		UT_User = 100
	};
}

#endif
