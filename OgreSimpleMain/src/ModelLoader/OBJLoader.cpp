#include "OBJLoader.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
namespace OgreSimple
{
	CLoadOBJ::CLoadOBJ()//
	{

	}
	CLoadOBJ::~CLoadOBJ()
	{
	    GLMgroup* obj = mModel.groups;
		while (obj)
        {
            GLMgroup* last = obj;
            obj = obj->next;
            delete last;
        }

	}

	GLMmodel* CLoadOBJ::load(string path)
	{
		size_t pos = path.find_last_of("/");
		string base_path = path.substr(0, pos+1);

		ifstream file(path.c_str(),ios::in);
		if (!file)
		{
			return NULL;
		}

		GLMgroup* group = new GLMgroup();
		group->name = "default";
		group->next = 0;

		mModel.groups = group;

		vector<Vector3> &vertexs = mModel.vertexs;
		vector<Vector3> &normals = mModel.normals;
		vector<Vector3> &texcoords = mModel.texcoords;
		int v,n,t;
		Vector3 tmp;
		GLMtriangle tri;

		char buf[128],str1[128],str2[128],str3[128];
		char tmpName[128] = {0};
		while (!file.eof())
		{
			file.getline(buf,128);
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
				mModel.mtllibname = tmpName;
				ReadMTL(mModel, base_path + tmpName);
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

		return &mModel;
	}

	void CLoadOBJ::ReadMTL(GLMmodel& model,string name)
	{
		vector<char> data;

		ifstream file(name.c_str(),ios::in);
		if (!file)
		{
			//assert(false && "文件不存在");
		}
		char buf[128] = {0};
		char tmpName[128] = {0};

		while( !file.eof() ) {

			file.getline( buf, 128 );
			char type[10] = {0};
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
