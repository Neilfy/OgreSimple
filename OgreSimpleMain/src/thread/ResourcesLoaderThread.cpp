#include "ResourcesLoaderThread.h"
#include "SceneManager.h"
namespace OgreSimple
{
    ResourcesLoaderThread::ResourcesLoaderThread(SceneManager* sceneMgr)
        :mSceneManger(sceneMgr)
    {
    }

    ResourcesLoaderThread::~ResourcesLoaderThread()
    {
    }

    void ResourcesLoaderThread::DoWork()
    {
        if(mTasks.empty())
        {
            return ;
        }

        std::string name = mTasks.front();
        //printf(name);
        if(mSceneManger)
        {
            MovableObject *obj = mSceneManger->CreateObject();
            mSceneManger->AttachObject(obj);
        }
        mTasks.pop();
    }

    void ResourcesLoaderThread::addTask(std::string resourceName)
    {
        mTasks.push(resourceName);
    }
}