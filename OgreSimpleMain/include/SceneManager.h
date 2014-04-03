#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//#include "Camera.h"
#include <string>
#include "MovableObject.h"
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

        //virtual void renderSingleObject(Renderable* rend);
    public:

        virtual void renderScene(RenderSystem* rs, Camera* cam, Viewport& vp);
        void CreateObject(/*Type*/);
        void LoadObject(/*file name*/);

    };
}
#endif
