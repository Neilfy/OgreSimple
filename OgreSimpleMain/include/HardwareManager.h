#ifndef HARDWAREMANAGER_H
#define HARDWAREMANAGER_H

namespace OgreSimple
{
    class HardwareManager
    {
    public:
        HardwareManager(){};
        virtual ~HardwareManager(){};

        virtual VertexVBO* creatVertexVBO() = 0;
        virtual IndexVBO* creatIndexVBO() = 0;
    };
}
#endif // HARDWAREMANAGER_H
