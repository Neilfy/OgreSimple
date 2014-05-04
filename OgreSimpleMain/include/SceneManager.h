#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "platform_thread.h"
#include <string>
#include <vector>
namespace OgreSimple
{
    class RenderSystem;
    class Viewport;
    class Camera;
    class MovableObject;
    class ResourcesLoaderThread;
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
        MovableObject* CreateObject(/*Type*/);
        void AttachObject(MovableObject* obj);
        void LoadSceneFile(/*file name*/);
    private:
        ResourcesLoaderThread* mThread;
    };
}
#endif
