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

    MovableObject* SceneManager::CreateObject()
    {
        //MovableObject *obj = new MovableObject();
        //obj->Make();
        VirtualObject *obj = new VirtualObject("tmp");
        obj->Make();
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
        mThread->addTask("tmp");

    }

}
