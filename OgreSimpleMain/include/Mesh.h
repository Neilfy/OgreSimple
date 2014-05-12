
#ifndef __Mesh_H__
#define __Mesh_H__

#include "SubMesh.h"
#include <string>
#include <vector>
namespace OgreSimple {


	class  Mesh
    {
	public:
		typedef std::vector<SubMesh*> SubMeshList;
	protected:
		SubMeshList mSubMeshList;
		std::string m_Name;

    public:
        Mesh(std::string name);
        ~Mesh();

		SubMesh* createSubMesh(void);
		void load();

		unsigned short getNumSubMeshes(void) const;
		SubMesh* getSubMesh(unsigned short index) const;
		std::string& getName()
		{
            return m_Name;
		}
    };



} // namespace

#endif
