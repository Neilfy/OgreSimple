#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//#include "Camera.h"
#include <string>
//#include "ColourValue.h"
namespace OgreSimple
{
	class RenderSystem;
	class Viewport;
	class Camera;
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

	private:
		RenderSystem* mRenderSystem;
		Camera* mCamera;
		
	protected:
		/// Instance name
		Viewport* mViewport;
		

		//virtual void renderSingleObject(Renderable* rend);
	public:
		
		virtual void renderScene(RenderSystem* rs, Camera* cam, Viewport* vp);

	};
}
#endif
