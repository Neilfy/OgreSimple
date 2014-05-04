#include "OBJLoader.h"
#include "Root.h"
#include "MeshManager.h"
#include "HardwareBufferManager.h"
#include "MaterialManager.h"
namespace OgreSimple
{
	CLoadOBJ::CLoadOBJ()//
	{

	}
	CLoadOBJ::~CLoadOBJ()
	{

	}

	bool CLoadOBJ::loadFromBuffer(string path)
	{
	    path = "E:\\WorkSpace\\OgreSimple\\Sample\\Resources\\Models\\tmp.obj";
		ifstream file(path.c_str(),ios::in);
		if (!file)
		{
			assert(false && "文件不存在");
		}

		GLMmodel model;
		GLMgroup* group = new GLMgroup();
		group->name = "default";
		group->next = 0;

		model.groups = group;

		vector<Vector3> &vertexs = model.vertexs;
		vector<Vector3> &normals = model.normals;
		vector<Vector3> &texcoords = model.texcoords;
		int v,n,t;
		Vector3 tmp;
		GLMtriangle tri;

		char buf[128],str1[128],str2[128],str3[128];
		char tmpName[128] = {0};
		while (!file.eof())
		{
			iss.getline(buf,128);
			char type[10]={0};
			sscanf(buf,"%[^ ]",type);
			sscanf( type, "%*[^a-z|A-Z|#]%s", type );
			switch(type[0])
			{
			case '#':
				break;
			case 'v':
				switch(type[1]) {
				case '\0':          /* vertex */
					sscanf(buf,"%*[^ ]%f %f %f",&(tmp.x),&(tmp.y),&(tmp.z));
					vertexs.push_back(tmp);
					break;
				case ':':          /* vertex */
					sscanf(buf,"%*[^ ]%f %f %f",&tmp.x,&tmp.y,&tmp.z);
					vertexs.push_back(tmp);
					break;
				case 'n':           /* normal */
					sscanf(buf,"%*[^ ]%f %f %f",&tmp.x,&tmp.y,&tmp.z);
					normals.push_back(tmp);
					break;
				case 't':           /* texcoord */
					sscanf(buf,"%*[^ ]%f %f",&tmp.x,&tmp.y);
					texcoords.push_back(tmp);
					break;
				default:
					;
				}
				break;
			case 'm':
				sscanf(buf, "%*[^ ]%s", tmpName);
				model.mtllibname = tmpName;
				ReadMTL(model, tmpName);
				break;
			case 'u':
				sscanf(buf,"%*[^ ]%s",tmpName);
				group->material = tmpName;
				break;
			case 'g':
				sscanf(buf,"%*[^ ]%s",tmpName);
				group->next = new GLMgroup;
				group = group->next;
				group->name = tmpName;
				group->next = 0;
				break;
			case 'f':
				v=n=t=0;
				tri.vIdx.clear();
				tri.nIdx.clear();
				tri.tIdx.clear();
				sscanf(buf,"%*[^ ]%s %s %s",str1,str2,str3);
				if (strstr(str1, "//")) {
					/* v//n */
					sscanf(str1, "%d//%d", &v, &n);
					tri.vIdx.push_back(v);
					tri.nIdx.push_back(n);
					sscanf(str2, "%d//%d", &v, &n);
					tri.vIdx.push_back(v);
					tri.nIdx.push_back(n);
					sscanf(str3, "%d//%d", &v, &n);
					tri.vIdx.push_back(v);
					tri.nIdx.push_back(n);
					group->triangles.push_back(tri);

				} else if (sscanf(str1, "%d/%d/%d", &v, &t, &n) == 3) {
					/* v/t/n */
					sscanf(str1, "%d/%d/%d", &v, &t, &n);
					tri.vIdx.push_back(v);
					tri.tIdx.push_back(t);
					tri.nIdx.push_back(n);
					sscanf(str2, "%d/%d/%d", &v, &t, &n);
					tri.vIdx.push_back(v);
					tri.tIdx.push_back(t);
					tri.nIdx.push_back(n);
					sscanf(str3, "%d/%d/%d", &v, &t, &n);
					tri.vIdx.push_back(v);
					tri.tIdx.push_back(t);
					tri.nIdx.push_back(n);
					group->triangles.push_back(tri);

				} else if (sscanf(str1, "%d/%d", &v, &t) == 2) {
					/* v/t */
					sscanf(str1, "%d/%d", &v, &t);
					tri.vIdx.push_back(v);
					tri.nIdx.push_back(t);
					sscanf(str2, "%d/%d", &v, &t);
					tri.vIdx.push_back(v);
					tri.nIdx.push_back(t);
					sscanf(str3, "%d/%d", &v, &t);
					tri.vIdx.push_back(v);
					tri.nIdx.push_back(t);
					group->triangles.push_back(tri);

				} else {
					/* v */
					sscanf(str1, "%d", &v);
					tri.vIdx.push_back(v);
					sscanf(str2, "%d", &v);
					tri.vIdx.push_back(v);
					sscanf(str2, "%d", &v);
					tri.vIdx.push_back(v);
					group->triangles.push_back(tri);

				}
				break;
			}
		}

		//

		//处理材质
		for(int i=0;i<model.materials.size();i++)
		{
			GLMmaterial& materials = model.materials[i];
			string name = materials.name;
			name = mesh->getName() + name;
			Material* pMat = MaterialManager::getSingleton().create(name);
			if (materials.texName != "")
			{
				pMat->createTextureUnitState( materials.texName );
			}


			pMat->setAmbient(materials.ambient[0], materials.ambient[1], materials.ambient[2]);
			pMat->setDiffuse(materials.diffuse[0], materials.diffuse[1], materials.diffuse[2],materials.diffuse[3]);
			pMat->setSpecular(materials.specular[0], materials.specular[1], materials.specular[2],materials.specular[3]);
			pMat->setShininess(materials.shininess);
			pMat->setLightingEnabled(true);
		}
		Vector3 minPt,maxPt;//box
		bool bFirst = true;

		GLMgroup* obj = model.groups;
		while (obj)
		{
			if (obj->triangles.size()==0)
			{
				GLMgroup* last = obj;
				obj = obj->next;
				delete last;
				continue;
			}
			vector<float> vecVertex;
			vector<GLMtriangle>::iterator tri_it = obj->triangles.begin();
			vector<GLMtriangle>::iterator tri_end = obj->triangles.end();
			for (; tri_it != tri_end; ++tri_it)
			{
				for (int i=0; i<3; i++)
				{
					if (tri_it->vIdx.size())
					{
						tmp = model.vertexs[tri_it->vIdx[i]-1];
						vecVertex.push_back(tmp.x);
						vecVertex.push_back(tmp.y);
						vecVertex.push_back(tmp.z);

						//box
						if (bFirst)
						{
							minPt = tmp;
							maxPt = tmp;
							bFirst = false;
						}else
						{
							minPt.x = tmp.x < minPt.x ? tmp.x : minPt.x ;
							maxPt.x = tmp.x > maxPt.x ? tmp.x : maxPt.x ;
							minPt.y = tmp.y < minPt.y ? tmp.y : minPt.y ;
							maxPt.y = tmp.y > maxPt.y ? tmp.y : maxPt.y ;
							minPt.z = tmp.z < minPt.z ? tmp.z : minPt.z ;
							maxPt.z = tmp.z > maxPt.z ? tmp.z : maxPt.z ;
						}
					}
					if (tri_it->nIdx.size())
					{
						tmp = model.normals[tri_it->nIdx[i]-1];
						vecVertex.push_back(tmp.x);
						vecVertex.push_back(tmp.y);
						vecVertex.push_back(tmp.z);
					}
					if (tri_it->tIdx.size())
					{
						tmp = model.texcoords[tri_it->tIdx[i]-1];
						vecVertex.push_back(tmp.x);
						vecVertex.push_back(tmp.y);
					}
				}
			}

			tri_it = obj->triangles.begin();
			VertexDeclaration* patchDecl;
			patchDecl = HardwareBufferManager::getSingleton().createVertexDeclaration();
			patchDecl->addElement(0, 0, VET_FLOAT3, VES_POSITION);
			if (tri_it->nIdx.size())
			{
				patchDecl->addElement(0, sizeof(float)*3, VET_FLOAT3, VES_NORMAL, 0);
			}
			if (tri_it->tIdx.size())
			{
				patchDecl->addElement(0, sizeof(float)*6, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
			}

			SubMesh* sm = mesh->createSubMesh();

			sm->vertexData = new VertexData();
			// Set up vertex buffer
			sm->vertexData->vertexStart = 0;
			sm->vertexData->vertexCount = obj->triangles.size()*3;
			sm->vertexData->vertexDeclaration = patchDecl;
			HardwareVertexBuffer* vbuf = HardwareBufferManager::getSingleton().
				createVertexBuffer(
				patchDecl->getVertexSize(0),
				sm->vertexData->vertexCount,
				HardwareBuffer::HBU_STATIC_WRITE_ONLY,
				true);

			vbuf->writeData(0,patchDecl->getVertexSize(0)*sm->vertexData->vertexCount,&vecVertex[0]);
			sm->vertexData->vertexBufferBinding->setBinding(0, vbuf);

			//设置材质
			string name = obj->material;
			name = mesh->getName() + name;
			sm->setMaterialName(name);
			sm->mMatInitialised = true;

			GLMgroup* last = obj;
			obj = obj->next;
			delete last;
		}
		Vector3 haf((maxPt.x-minPt.x)*0.5, (maxPt.y-minPt.y)*0.5, (maxPt.z-minPt.z)*0.5);
		AABB box(Vector3(0,0,0),haf);

		mesh->_setBounds(box);
		return true;
	}

	void CLoadOBJ::ReadMTL(GLMmodel& model,string name)
	{
		//string basePath = Root::getSingleton().getResourcePath();
#ifdef WIN32
		basePath += "\\Model\\";
#else
		basePath += "/Model/";
#endif
		vector<char> data;
		basePath += name;

		ifstream file(basePath.c_str(),ios::in);
		if (!file)
		{
			assert(false && "文件不存在");
		}
		char buf[128],tmpName[128];

		while( !file.eof() ) {

			file.getline( buf, 128 );
			char type[ 10 ];
			sscanf( buf, "%[^ ]",type );
			sscanf( type, "%*[^a-z|A-Z|#]%s", type );

			switch( type[ 0 ] ) {
			case '#':               /* comment */
				break;
			case 'n':               /* newmtl */
				sscanf(buf, "%*[^ ]%s", tmpName);
				model.materials.push_back(GLMmaterial());
				model.materials[model.materials.size()-1].name = tmpName;
				break;
			case 'N':
				if (!strcmp(type ,"Ns"))
				{
					sscanf(buf, "%*[^ ]%f", &model.materials[model.materials.size()-1].shininess);
				}
				break;
			case 'K':
				switch(type[1]) {
				case 'd':
					sscanf(buf, "%*[^ ]%f %f %f",
						&model.materials[model.materials.size()-1].diffuse[0],
						&model.materials[model.materials.size()-1].diffuse[1],
						&model.materials[model.materials.size()-1].diffuse[2]);
					model.materials[model.materials.size()-1].diffuse[3] = 1.0;
					break;
				case 's':
					sscanf(buf, "%*[^ ]%f %f %f",
						&model.materials[model.materials.size()-1].specular[0],
						&model.materials[model.materials.size()-1].specular[1],
						&model.materials[model.materials.size()-1].specular[2]);
					model.materials[model.materials.size()-1].specular[3] = 1.0;
					break;
				case 'a':
					sscanf(buf, "%*[^ ]%f %f %f",
						&model.materials[model.materials.size()-1].ambient[0],
						&model.materials[model.materials.size()-1].ambient[1],
						&model.materials[model.materials.size()-1].ambient[2]);
					model.materials[model.materials.size()-1].ambient[3] = 1.0;
					break;
				default:
					/* eat up rest of line */
					break;
				}
				break;
			case 'm':
				if (!strcmp(type ,"map_Kd"))
				{
					sscanf(buf,"%*[^ ]%s",tmpName);
					model.materials[model.materials.size()-1].texName = tmpName;
				}
				break;
			default:
				/* eat up rest of line */

				break;
			}
		}
	}



}
