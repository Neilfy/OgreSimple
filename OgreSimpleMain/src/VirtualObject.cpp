#include "VirtualObject.h"
#include "RenderOperation.h"
#include "RenderSystem.h"
#include "OBJLoader.h"
namespace OgreSimple
{
    VirtualObject::VirtualObject(std::string name)
	:mName(name)
    {
    }

    VirtualObject::~VirtualObject()
    {
    }

    void VirtualObject::Make()
    {
        CLoadOBJ objLoader;
        GLMmodel *model = objLoader.load("tmp.obj");

        GLMgroup* obj = model->groups;
                while (obj)
                {
                        if (obj->triangles.size()==0)
                        {
                                obj = obj->next;
                                continue;
                        }
                        vector<float> vecVertex;
                        Vector3 tmp;
                        int vertex_count = 0;
                        vector<GLMtriangle>::iterator tri_it = obj->triangles.begin();
                        vector<GLMtriangle>::iterator tri_end = obj->triangles.end();

                        for (; tri_it != tri_end; ++tri_it)
                        {
                                for (int i=0; i<3; i++)
                                {
                                        if (tri_it->vIdx.size())
                                        {
                                                tmp = model->vertexs[tri_it->vIdx[i]-1];
                                                vecVertex.push_back(tmp.x);
                                                vecVertex.push_back(tmp.y);
                                                vecVertex.push_back(tmp.z);

                                                vertex_count ++;

                                        }
                                        if (tri_it->nIdx.size())
                                        {
                                                tmp = model->normals[tri_it->nIdx[i]-1];
                                                vecVertex.push_back(tmp.x);
                                                vecVertex.push_back(tmp.y);
                                                vecVertex.push_back(tmp.z);

                                        }
					if (tri_it->tIdx.size())
                                        {
                                                tmp = model->texcoords[tri_it->tIdx[i]-1];
                                                vecVertex.push_back(tmp.x);
                                                vecVertex.push_back(tmp.y);
                                        }
                                }
                        }

                        tri_it = obj->triangles.begin();
			int verType = FVF_POSITION;
                        if (tri_it->nIdx.size())
                        {
				verType |= FVF_NORMAL;
                        }
                        if (tri_it->tIdx.size())
                        {
                                verType |= FVF_UV;
                        }
			ObjectSection *section = new ObjectSection();
			int size_byte = vecVertex.size() * sizeof(float);
			section->createVertexData(verType, vertex_count, false);
        		section->addVertices((uint8*)&vecVertex[0], size_byte);
			mSections.push_back(section);
                        obj = obj->next;
		}

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
