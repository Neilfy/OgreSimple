#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include <vector>
#include "Renderable.h"

namespace OgreSimple
{
    class RenderSystem;
    class MovableObject
    {
    public:
        class ObjectSection : public Renderable
        {
        public:
            ObjectSection();
            virtual ~ObjectSection();

            void render(RenderSystem* renderer);
        };

    public:
        MovableObject();
        virtual ~MovableObject();

        virtual void Make();
        virtual void render(RenderSystem* renderer);
    private:
        std::vector<ObjectSection*> mSections;

    };
}
#endif
