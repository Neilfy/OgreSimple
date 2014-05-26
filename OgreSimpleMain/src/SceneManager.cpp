#include "SceneManager.h"
#include "OgreSimpleRoot.h"
#include "RenderSystem.h"
#include "Viewport.h"
#include "Camera.h"
#include "MovableObject.h"
#include "ResourcesLoaderThread.h"
#include "VirtualObject.h"
#include "SceneFileLoader.h"
namespace OgreSimple
{
    SceneManager::SceneManager()
        :mThread(NULL)
    {
        mThread = new ResourcesLoaderThread(this);
        mThread->Start();
    }
    SceneManager::~SceneManager()
    {
        std::vector<MovableObject*>::iterator iter;
        for(iter = mQueue.begin(); iter != mQueue.end(); ++iter)
        {
            MovableObject *obj = *iter;
            delete obj;
        }

        mThread->Stop();
        delete mThread;

    }

    void SceneManager::renderScene(RenderSystem* rs, Camera* cam, Viewport& vp)
    {
        mCamera = cam;
        mRenderSystem = rs;
        mCamera->SetViewport(vp);
        rs->setViewport(vp);
        rs->setProjectionMatrix(cam->GetProjectionMatrix());
        rs->setViewMatrix(cam->GetViewMatrix());

		rs->clearFrameBuffer();

        mLocker.SyncStart();
        std::vector<MovableObject*>::iterator iter;
        uint32 pid = GetCurrentThreadId();
        printf("=====queue size==%d\n",mQueue.size());
        for(iter = mQueue.begin(); iter != mQueue.end(); ++iter)
        {
            MovableObject *obj = *iter;
            printf("*****star render***%x \n", obj);
            obj->render(mRenderSystem);
            printf("*****end render***%x \n", obj);
        }
        mLocker.SyncEnd();

        // Clear the viewport if required
        //if (mViewport->getClearEveryFrame())
        {
            //mDestRenderSystem->clearFrameBuffer(
            //    mViewport->getClearBuffers(),
            //    mViewport->getBackgroundColour());
        }

    }

    MovableObject* SceneManager::CreateObject(ResourceInfo objInfo)
    {
        MovableObject *obj = NULL;
		if(objInfo.type == 1)
		{
			obj = new VirtualObject(objInfo.name);
			((VirtualObject*)obj)->setMeshFile(objInfo.path);
			obj->Make();
			obj->setPosition(objInfo.pos);
		}else if(objInfo.type == 2)
		{
			obj = new MovableObject();
			obj->Make();
			obj->setPosition(objInfo.pos);
		}
		uint32 pid = GetCurrentThreadId();
		printf("======return obj pid:%d,obj:%x\n", pid,obj);
		return obj;
    }

    void SceneManager::AttachObject(MovableObject* obj)
    {
        mLocker.SyncStart();
        mQueue.push_back(obj);
        uint32 pid = GetCurrentThreadId();
        printf("======add obj pid:%d,obj:%x,queue obj:%x\n", pid,obj,mQueue[mQueue.size()-1]);
        mLocker.SyncEnd();
    }

    void SceneManager::LoadSceneFile()
    {
        //TODO
        //temp source code for testing Resource loader thread.
        //ResourceInfo task_info = {"F-35_Lightning_II/F-35_Lightning_II.obj", "F-35_Lightning_II/F-35_Lightning_II.obj", Vector3(0,0,10)};
        //ResourceInfo task_info = {"tmp/tmp.obj", "tmp/tmp.obj", Vector3(0,0,10)};
        //mThread->addTask(task_info);
        std::string base_path = OgreSimpleRoot::getSingleton()->getResourcePath();

		base_path += "/test.xml";
        SceneFileLoader loader(mThread);
        loader.loadFile(base_path);

    }

}
