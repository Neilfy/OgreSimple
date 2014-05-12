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
        Vector3 pos;
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
