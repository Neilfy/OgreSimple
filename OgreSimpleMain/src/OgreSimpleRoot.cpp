#include <assert.h>
#include <stdio.h>
//#include "Common.h"
#include "OgreSimpleRoot.h"

#include "SceneManager.h"
#include "Camera.h"
//#include "FrameListener.h"
#include "RenderSystem.h"
//#include "GLRenderSystem.h"
//#include "RenderWindow.h"
//#include "MovableObject.h"
#include "MeshManager.h"
#include "MaterialManager.h"
//#include "Entity.h"
//#include "Light.h"
namespace OgreSimple
{
    OgreSimpleRoot * OgreSimpleRoot::ms_Singleton = NULL;

    OgreSimpleRoot::OgreSimpleRoot(void)
                        :mViewport(0, 0, 0, 0)
                        ,mSceneManager(NULL)
                        ,mCamera(NULL)
                        ,mRenderer(NULL)
    {
        ms_Singleton = this;
        mMatManager = new MaterialManager();

        mMeshManager = new MeshManager();
        //mMatManager = new MaterialManager;

        //mEntityFactory = new EntityFactory();
        //addMovableObjectFactory(mEntityFactory);
        //mLightFactory = new LightFactory();
        //addMovableObjectFactory(mLightFactory);
    }

    OgreSimpleRoot::~OgreSimpleRoot(void)
    {
        if(mSceneManager)
        {
            delete mSceneManager;
        }

        if(mCamera)
        {
            delete mCamera;
        }

        if(mRenderer)
        {
            delete mRenderer;
        }

		if(mMeshManager)
		{
			delete mMeshManager;
		}

		if(mMatManager)
		{
			delete mMatManager;
		}

        //delete mMeshManager;
        //delete mMatManager;
        //delete mEntityFactory;
        //delete mLightFactory;
        //delete mActiveRenderer;
        ms_Singleton = 0;
    }

    void OgreSimpleRoot::initialise()
    {
        mMatManager->initialise();
    }

    void OgreSimpleRoot::setRenderSystem(RenderSystem* system)
    {
        if(!mRenderer)
        {
            mRenderer = system;
            mRenderer->initialise();
        }
    }

    void OgreSimpleRoot::setSurfaceSize(int width, int height)
    {
        mViewport.SetSize(0, 0, width, height);
    }

    SceneManager* OgreSimpleRoot::createSceneManager()
    {
        if(!mSceneManager)
        {
            mSceneManager = new SceneManager();
        }
        return mSceneManager;
    }

    Camera* OgreSimpleRoot::createCamera()
    {
        if(!mCamera)
        {
            mCamera = new Camera();
        }
        return mCamera;
    }

    Camera* OgreSimpleRoot::getCamera() const
    {
        return mCamera;
    }

    void OgreSimpleRoot::renderScene()
    {
        mSceneManager->renderScene(mRenderer, mCamera, mViewport);
    }

}



