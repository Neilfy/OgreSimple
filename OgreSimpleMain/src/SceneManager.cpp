#include "SceneManager.h"
#include "OgreSimpleRoot.h"
#include "RenderSystem.h"
#include "Viewport.h"
#include "Camera.h"
#include "MovableObject.h"

namespace OgreSimple
{
    SceneManager::SceneManager()
    {

    }
    SceneManager::~SceneManager()
    {
        std::vector<MovableObject*>::iterator iter;
        for(iter = mQueue.begin(); iter != mQueue.end(); ++iter)
        {
            MovableObject *obj = *iter;
            delete obj;
        }

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

    void SceneManager::CreateObject()
    {
        MovableObject *obj = new MovableObject();
        obj->Make();

        mQueue.push_back(obj);
    }

    void SceneManager::LoadObject()
    {
        //TODO
    }

}
