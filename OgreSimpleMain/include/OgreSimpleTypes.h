#ifndef OGRESIMPLE_TYPES_H
#define OGRESIMPLE_TYPES_H

namespace OgreSimple
{
#ifndef NULL
#define NULL 0

#define FVF_POSITION 0x00000001
#define FVF_NORMAL 0x00000002
#define FVF_DIFFUSE 0x00000004
#define FVF_UV 0x00000008

#endif
    typedef unsigned long long uint64;
    typedef unsigned int uint32;
    typedef unsigned short uint16;
    typedef unsigned char uint8;
    typedef int int32;
    typedef short int16;
    typedef char int8;

    static const float ME_PI = 3.141592654f;
}

#endif
