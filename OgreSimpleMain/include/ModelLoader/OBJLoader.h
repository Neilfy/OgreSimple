#ifndef CLOADOBJ_H
#define CLOADOBJ_H

#include "NMath.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

namespace OgreSimple
{
	typedef struct _GLMmaterial
                {
                  string   name;                 /* name of material */
                  float diffuse[4];           /* diffuse component */
                  float ambient[4];           /* ambient component */
                  float specular[4];          /* specular component */
                  float emmissive[4];         /* emmissive component */
                  float shininess;            /* specular exponent */
                  string texName;
                } GLMmaterial;

                /* GLMtriangle: Structure that defines a triangle in a model.
                 */
                typedef struct _GLMtriangle {
                  vector<int>   vIdx;
                  vector<int>  nIdx;
                  vector<int>   tIdx;
                } GLMtriangle;

                /* GLMgroup: Structure that defines a group in a model.
                 */
                typedef struct _GLMgroup {
                  string             name;           /* name of this group */
                  vector<GLMtriangle>           triangles;      /* array of triangle indices */
                  string            material;       /* index to material for group */
                  struct _GLMgroup* next;           /* pointer to next group in model */
                } GLMgroup;
                typedef struct _GLMmodel {
                        string    mtllibname;          /* name of the material library */
                        vector<Vector3> vertexs;
                        vector<Vector3> normals;
                        vector<Vector3> texcoords;
                        GLMgroup*    groups;          /* linked list of groups */
                        vector<GLMmaterial> materials;

                } GLMmodel;

	class CLoadOBJ
	{
	public:
		CLoadOBJ();								// 初始化数据成员
		virtual ~CLoadOBJ();

		GLMmodel* load(string path);
	private:
		void ReadMTL(GLMmodel& model,string name);
		GLMmodel mModel;


	};
}
#endif
