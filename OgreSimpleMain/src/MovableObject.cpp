#include "MovableObject.h"
#include "RenderOperation.h"
#include "RenderSystem.h"
#include "MaterialManager.h"
#include "Material.h"
namespace OgreSimple
{
    MovableObject::ObjectSection::ObjectSection()
        :mMat(NULL)
    {
    }

    MovableObject::ObjectSection::~ObjectSection()
    {
    }

    void MovableObject::ObjectSection::render(RenderSystem* renderer)
    {
        if(mMat)
        {
            renderer->setMaterial(mMat);
        }
        RenderOperation ro;
        ro.mVertexData = getVertexData();
        ro.mIndexData = getIndexData();

        renderer->render(&ro);
    }

    void MovableObject::ObjectSection::setMaterial(Material* mat)
    {
         mMat = mat;
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
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        int index[]={
            0,1,2
        };

        section->createVertexData(FVF_POSITION|FVF_UV, 3, false);
        section->addVertices((uint8*)buf, sizeof(buf));

        section->createIndexData(IT_32BIT, 3, false);
        section->addIndexes((uint8*)index, sizeof(index));

        Material* mat = MaterialManager::getSingleton()->create("test");
        Technique* tec = mat->createTechnique();
        TextureUnit* texUnit = tec->CreateTextureUnit();
        texUnit->SetPicName("test");
        section->setMaterial(mat);

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
