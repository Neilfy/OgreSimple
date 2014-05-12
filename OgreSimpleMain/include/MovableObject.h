#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include <vector>
#include "NMath.h"

namespace OgreSimple
{
    class RenderSystem;
    class Material;
    class Mesh;
    class MovableObject
    {
    public:
        MovableObject();
        virtual ~MovableObject();

        virtual void Make();
        virtual void render(RenderSystem* renderer);
        virtual void setPosition(Vector3& pos);
        virtual void setScale(Vector3& scale);
        virtual Matrix4& getTransform();
    protected:
        Mesh* mMesh;
        Vector3 mPosition;
        Vector3 mScale;
        Matrix4 mTransform;
        bool mIsTransformNeedUpdate;
    };
}
#endif
