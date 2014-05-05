#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include <vector>
#include "Renderable.h"

namespace OgreSimple
{
    class RenderSystem;
    class Material;
    class MovableObject
    {
    public:
        class ObjectSection : public Renderable
        {
        public:
            ObjectSection();
            virtual ~ObjectSection();

            void render(RenderSystem* renderer);

            void setMaterial(Material* mat);

        private:
            Material* mMat;
        };

    public:
        MovableObject();
        virtual ~MovableObject();

        virtual void Make();
        virtual void render(RenderSystem* renderer);
    protected:
        std::vector<ObjectSection*> mSections;

    };
}
#endif
