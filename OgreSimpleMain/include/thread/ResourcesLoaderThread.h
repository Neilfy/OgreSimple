#ifndef RESOURCESLOADERTHREAD_H
#define RESOURCESLOADERTHREAD_H

#include "ThreadBase.h"
#include <queue>
#include <string>
namespace OgreSimple
{
    class SceneManager;
    class ResourcesLoaderThread : public ThreadBase
    {
    public:
        ResourcesLoaderThread(SceneManager* sceneMgr);
        ~ResourcesLoaderThread();

        virtual void DoWork();
        void addTask(std::string resourceName);
    private:
        std::queue<std::string> mTasks;
        SceneManager* mSceneManger;
    };
}

#endif
