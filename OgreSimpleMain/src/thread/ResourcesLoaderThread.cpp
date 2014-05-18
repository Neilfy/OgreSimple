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

        ResourceInfo task_info = mTasks.front();
        //printf(name);
        if(mSceneManger)
        {
            MovableObject *obj = mSceneManger->CreateObject(task_info);
			if(obj)
				mSceneManger->AttachObject(obj);
        }
        mTasks.pop();
    }

    void ResourcesLoaderThread::addTask(ResourceInfo taskInfo)
    {
        mTasks.push(taskInfo);
    }
}
