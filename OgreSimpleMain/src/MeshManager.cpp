#include "MeshManager.h"

namespace OgreSimple
{
	MeshManager* MeshManager::ms_Singleton = 0;

	MeshManager::MeshManager()
	{
		ms_Singleton =  this ;
	}
	MeshManager::~MeshManager()
	{
	    std::map<std::string, Mesh*>::iterator it, it_end;
		it_end = mMeshes.end();
		for ( it = mMeshes.begin(); it != it_end; ++it )
		{
			delete it->second;
		}
		mMeshes.clear();
		ms_Singleton = 0;
	}

	MeshManager* MeshManager::getSingleton()
	{
		//assert( ms_Singleton );
		return ms_Singleton;
	}
	Mesh* MeshManager::createManual(const std::string& name)
	{
		return create(name,true);
	}

	Mesh* MeshManager::load(const std::string &name)
	{
		std::map<std::string, Mesh*>::iterator it = mMeshes.find(name);
		if (it != mMeshes.end())
		{
			return it->second;
		}else
		{
			Mesh *res = create(name,false);
			res->load();
			return res;
		}
	}

	Mesh* MeshManager::create(const std::string& name,bool isManual)
	{
		Mesh* ret = new Mesh(name);
		mMeshes.insert(make_pair(ret->getName(), ret));

		return ret;
	}



}
