
#ifndef __MeshManager_H__
#define __MeshManager_H__

#include "Mesh.h"
#include <string>
#include <map>
namespace OgreSimple{

	class  MeshManager
    {
    public:
		MeshManager();
		~MeshManager();
		static MeshManager* getSingleton();

		Mesh* load(const std::string& name);
		Mesh* createManual(const std::string& name);
		Mesh* create(const std::string& name,bool isManual);
	private:
		static MeshManager* ms_Singleton;
		std::map<std::string, Mesh*>	mMeshes;

    };


} //namespace

#endif
