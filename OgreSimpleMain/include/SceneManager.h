#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//#include "Camera.h"
#include <string>
#include <vector>
namespace OgreSimple
{
    class RenderSystem;
    class Viewport;
    class Camera;
    class MovableObject;
    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

    private:
        RenderSystem *mRenderSystem;
        Camera *mCamera;

         std::vector<MovableObject*> mQueue;

    protected:

        //virtual void renderSingleObject(Renderable* rend);
    public:

        virtual void renderScene(RenderSystem* rs, Camera* cam, Viewport& vp);
        void CreateObject(/*Type*/);
        void LoadObject(/*file name*/);

    };
}
#endif
