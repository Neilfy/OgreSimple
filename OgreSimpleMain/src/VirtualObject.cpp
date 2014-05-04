#include "VirtualObject.h"
#include "RenderOperation.h"
#include "RenderSystem.h"
#include "OBJLoader.h"
namespace OgreSimple
{
    VirtualObject::VirtualObject()
    {
    }

    VirtualObject::~VirtualObject()
    {
        std::vector<ObjectSection*>::iterator iter;
        for(iter = mSections.begin(); iter != mSections.end(); ++iter)
        {
            ObjectSection *section = *iter;
            delete section;
        }
    }

    void VirtualObject::Make()
    {
        CLoadOBJ objLoader;
        objLoader.load("tmp.obj");
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

    void VirtualObject::render(RenderSystem* renderer)
    {
        std::vector<ObjectSection*>::iterator iter;
        for(iter = mSections.begin(); iter != mSections.end(); ++iter)
        {
            ObjectSection *section = *iter;
            section->render(renderer);
        }
    }
}
