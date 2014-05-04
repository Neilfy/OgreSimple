#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "MovableObject.h"

namespace OgreSimple
{
    class VirtualObject
    {
    public:
        VirtualObject(std::string name);
        virtual ~VirtualObject();

        virtual void Make();
        virtual void render(RenderSystem* renderer);
    private:
        std::string mName;
    };
}
#endif
