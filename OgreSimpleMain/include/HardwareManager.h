#ifndef HARDWAREMANAGER_H
#define HARDWAREMANAGER_H

namespace OgreSimple
{
    class VertexVBO;
    class IndexVBO;
    class HardwareManager
    {
    public:
        HardwareManager();
        virtual ~HardwareManager();

        static HardwareManager* getSingleton();

        virtual VertexVBO* creatVertexVBO() = 0;
        virtual IndexVBO* creatIndexVBO() = 0;

    private:
        static HardwareManager* mSingleton;
    };
}
#endif // HARDWAREMANAGER_H
