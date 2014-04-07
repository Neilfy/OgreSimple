#include "MovableObject.h"
#include "RenderOperation.h"
#include "RenderSystem.h"
namespace OgreSimple
{
    MovableObject::ObjectSection::ObjectSection()
    {
    }

    MovableObject::ObjectSection::~ObjectSection()
    {
    }

    void MovableObject::ObjectSection::render(RenderSystem* renderer)
    {
         RenderOperation ro;
         ro.mVertexData = getVertexData();

         renderer->render(&ro);
    }
    //====================================================
    MovableObject::MovableObject()
    {
    }

    MovableObject::~MovableObject()
    {
        std::vector<ObjectSection*>::iterator iter;
        for(iter = mSections.begin(); iter != mSections.end(); ++iter)
        {
            ObjectSection *section = *iter;
            delete section;
        }
    }

    void MovableObject::Make()
    {
        ObjectSection *section = new ObjectSection();
        float buf[]={
            0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };

        section->createVertexData(FVF_POSITION, 3);
        section->addVertices((uint8*)buf, sizeof(buf));

        mSections.push_back(section);
    }

    void MovableObject::render(RenderSystem* renderer)
    {
        std::vector<ObjectSection*>::iterator iter;
        for(iter = mSections.begin(); iter != mSections.end(); ++iter)
        {
            ObjectSection *section = *iter;
            section->render(renderer);
        }
    }
}
