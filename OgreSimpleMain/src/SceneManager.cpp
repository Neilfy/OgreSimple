#include "SceneManager.h"
#include "OgreSimpleRoot.h"
#include "RenderSystem.h"
#include "Viewport.h"
#include "Camera.h"
#include "MovableObject.h"
#include "ResourcesLoaderThread.h"
#include "VirtualObject.h"
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

        std::vector<MovableObject*>::iterator iter;
        for(iter = mQueue.begin(); iter != mQueue.end(); ++iter)
        {
            MovableObject *obj = *iter;
            obj->render(mRenderSystem);
        }

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
        //MovableObject *obj = new MovableObject();
        //obj->Make();
        VirtualObject *obj = new VirtualObject(objInfo.name);
        obj->Make();
		obj->setPosition(objInfo.pos);
		Vector3 scale(2, 2, 2);
		obj->setScale(scale);
        return obj;
    }

    void SceneManager::AttachObject(MovableObject* obj)
    {
        mQueue.push_back(obj);
    }

    void SceneManager::LoadSceneFile()
    {
        //TODO
        //temp source code for testing Resource loader thread.
        ResourceInfo task_info = {"F-35_Lightning_II/F-35_Lightning_II.obj", "F-35_Lightning_II/F-35_Lightning_II.obj", Vector3(0,0,10)};
        //ResourceInfo task_info = {"tmp/tmp.obj", "tmp/tmp.obj", Vector3(0,0,10)};
        mThread->addTask(task_info);

    }

}
