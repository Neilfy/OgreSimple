#include "SceneManager.h"
#include "OgreSimpleRoot.h"
#include "RenderSystem.h"
#include "Viewport.h"
#include "Camera.h"

namespace OgreSimple
{
    SceneManager::SceneManager()
    {

    }
    SceneManager::~SceneManager()
    {

    }

    void SceneManager::renderScene(RenderSystem* rs, Camera* cam, Viewport& vp)
    {
        mCamera = cam;
        mRenderSystem = rs;
        mCamera->SetViewport(vp);
        rs->setViewport(vp);
                rs->setProjectionMatrix(cam->GetProjectionMatrix());
                rs->setViewMatrix(cam->GetViewMatrix());
        rs->render();

        // Clear the viewport if required
        //if (mViewport->getClearEveryFrame())
        {
            //mDestRenderSystem->clearFrameBuffer(
            //    mViewport->getClearBuffers(), 
            //    mViewport->getBackgroundColour());
        }
        
    }

}
