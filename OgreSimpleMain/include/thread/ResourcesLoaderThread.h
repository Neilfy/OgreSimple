#ifndef RESOURCESLOADERTHREAD_H
#define RESOURCESLOADERTHREAD_H

#include "ThreadBase.h"
#include "NMath.h"
#include <queue>
#include <string>

namespace OgreSimple
{
    struct ResourceInfo
    {
        std::string name;
        std::string path;
        unsigned char type;//1 model 2 box...
		Vector3 size;
		std::string texture;
		Vector3 pos;
		Vector3 scale;
    };

    class SceneManager;
    class ResourcesLoaderThread : public ThreadBase
    {
    public:
        ResourcesLoaderThread(SceneManager* sceneMgr);
        ~ResourcesLoaderThread();

        virtual void DoWork();
        void addTask(ResourceInfo taskInfo);
    private:
        std::queue<ResourceInfo> mTasks;
        SceneManager* mSceneManger;
    };
}

#endif
