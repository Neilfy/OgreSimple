#include <assert.h>
//#include "Common.h"
#include "OgreSimpleRoot.h"
#include "Viewport.h"
#include "SceneManager.h"
#include "Camera.h"
//#include "FrameListener.h"
#include "RenderSystem.h"
//#include "GLRenderSystem.h"
//#include "RenderWindow.h"
//#include "MovableObject.h"
//#include "MeshManager.h"
//#include "MaterialManager.h"
//#include "Entity.h"
//#include "Light.h"
namespace OgreSimple
{
	OgreSimpleRoot * OgreSimpleRoot::ms_Singleton = NULL;

	OgreSimpleRoot::OgreSimpleRoot(void)
	{
		ms_Singleton = this;
		mSceneManager = NULL;
		mCamera = NULL;
		mRenderer = NULL;
		mViewport = NULL;
		//mMeshManager = new MeshManager();
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

		if(mViewport)
		{
			delete mViewport;
		}
		//delete mMeshManager;
		//delete mMatManager;
		//delete mEntityFactory;
		//delete mLightFactory;
		//delete mActiveRenderer;
		ms_Singleton = 0;
	}
	
	void OgreSimpleRoot::setSurfaceSize(int width, int height)
	{
		if(!mViewport)
		{
			mViewport = new Viewport(0, 0, width, height, Color::Black, 0.1, 100.0);
		}
	}
	
	void OgreSimpleRoot::setRenderSystem(RenderSystem* system)
	{
		if(!mRenderer)
		{
			mRenderer = system;
		}
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
			Camera *mCamera = new Camera();
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



