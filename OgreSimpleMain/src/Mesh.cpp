#include "Mesh.h"
#include "SubMesh.h"
#include "OgreSimpleRoot.h"
#include "MaterialManager.h"
#include "Material.h"
#include "ModelLoader/OBJLoader.h"
#include <algorithm>
namespace OgreSimple {

    Mesh::Mesh(std::string name)
    {
		m_Name = name;
    }
    //-----------------------------------------------------------------------
    Mesh::~Mesh()
    {
		SubMeshList::iterator it, it_end;
		it_end = mSubMeshList.end();
		for (it = mSubMeshList.begin(); it != it_end; ++it)
		{
			delete *it;
		}
    }

	void Mesh::load()
	{
        std::string base_path = OgreSimpleRoot::getSingleton()->getResourcePath();
        std::string file_path = base_path + "/Models/" + m_Name;
        CLoadOBJ objLoader;
        GLMmodel *model = objLoader.load(file_path);
        for(int i=0;i<model->materials.size();i++)
        {
            GLMmaterial& materials = model->materials[i];
			Material* mat = MaterialManager::getSingleton()->create(materials.name);
			if(mat)
			{
                Technique* tec = mat->createTechnique();
                        //tec->mAmbient = Color(materials.ambient[0], materials.ambient[1], materials.ambient[2]);
                        //tec->mDiffuse = Color(materials.diffuse[0], materials.diffuse[1], materials.diffuse[2],materials.diffuse[3]);
                        //tec->mSpecular = Color(materials.specular[0], materials.specular[1], materials.specular[2],materials.specular[3]);
                        //tec->mShininess = materials.shininess;
                        //tec->mLightingEnabled = false;
                if(!materials.texName.empty())
                {
                    std::string tex_dir = "Models/";
					size_t pos = m_Name.find_last_of("/");
                    tex_dir += m_Name.substr(0, pos+1);
					
					TextureUnit* texUnit = tec->CreateTextureUnit();
					texUnit->SetPicName(tex_dir + materials.texName);
					texUnit->LoadTexture();
                }

			}
        }

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
            SubMesh *sub = createSubMesh();
			int size_byte = vecVertex.size() * sizeof(float);
			sub->createVertexData(verType, vertex_count, false);
            sub->addVertices((uint8*)&vecVertex[0], size_byte);

			sub->setMaterialName(obj->material);

            obj = obj->next;
		}
	}

	SubMesh* Mesh::createSubMesh()
	{

		SubMesh* sub = new SubMesh();
		sub->parent = this;

		mSubMeshList.push_back(sub);

		return sub;
	}

	unsigned short Mesh::getNumSubMeshes() const
	{
		return static_cast< unsigned short >( mSubMeshList.size() );
	}

	SubMesh* Mesh::getSubMesh(unsigned short index) const
	{
		if (index >= mSubMeshList.size())
		{
			//assert(false);
		}

		return mSubMeshList[index];
	}

}

