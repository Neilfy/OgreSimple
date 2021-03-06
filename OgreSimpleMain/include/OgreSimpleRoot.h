#ifndef OGRESIMPLE_ROOT_H
#define  OGRESIMPLE_ROOT_H

#include<string>
#include "Viewport.h"
namespace OgreSimple
{
    class SceneManager;
    class MeshManager;
    class MaterialManager;
    class ShaderManager;
    class RenderSystem;
    class Viewport;
    class Camera;

    class OgreSimpleRoot
    {
    private:
        SceneManager* mSceneManager;
        Camera* mCamera;
        RenderSystem* mRenderer;
        static OgreSimpleRoot *ms_Singleton;
        Viewport mViewport;
        MeshManager* mMeshManager;
        MaterialManager* mMatManager;
        ShaderManager* mShaderManager;
        std::string m_BasePath;
    protected:
        //typedef std::map<string, MovableObjectFactory*> MovableObjectFactoryMap;
        //MovableObjectFactoryMap mMovableObjectFactoryMap;
        //MovableObjectFactory* mEntityFactory;
        //MovableObjectFactory* mLightFactory;
        //std::set<FrameListener*> mFrameListeners;
    public:

        OgreSimpleRoot(void);
        ~OgreSimpleRoot(void);
        static OgreSimpleRoot* getSingleton(){ return ms_Singleton; };

        std::string getResourcePath(){ return m_BasePath; };
        void setResourcePath(std::string path){ m_BasePath = path; };

        void setRenderSystem(RenderSystem* system);
        void initialise();
        void setSurfaceSize(int width, int height);
        SceneManager* createSceneManager();

        virtual Camera* createCamera();
        virtual Camera* getCamera() const;

        void renderScene();

        //MovableObjectFactory* getMovableObjectFactory(const string& typeName);
        //void addMovableObjectFactory(MovableObjectFactory* fact,
        //    bool overrideExisting = false);

    private:
        bool _updateAllRenderTargets(void);

    };
}

#endif
