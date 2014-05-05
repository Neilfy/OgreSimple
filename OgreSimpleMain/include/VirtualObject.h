#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H

#include "MovableObject.h"
#include <string>
namespace OgreSimple
{
    class RenderSystem;
    class VirtualObject : public MovableObject
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
