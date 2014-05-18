#ifndef SCENEFILELOADER_H
#define SCENEFILELOADER_H
#include "tinyXML/tinyxml.h"
#include "tinyXML/tinystr.h"
#include "NMath.h"
#include <string>
#include <vector>
using namespace std;
namespace OgreSimple
{
    class ResourcesLoaderThread;
	class SceneFileLoader
	{

	public:
		struct NODE
		{
			string name;
			unsigned char type;
			string mesh;
			string texture;
			Vector3 size;
			Vector3 position;
			Vector3 scale;
			vector<NODE> nodes;
		};

		SceneFileLoader(ResourcesLoaderThread* worker);
		~SceneFileLoader(){};

		void loadFile(string path);
		void createEntitys(vector<NODE>& nodes);

		void splitString(const string& src, const string& tok, vector<string>& vecStrOut);
		float parseFloat(const string& val);

	private:
		vector<NODE> m_Nodes;
		ResourcesLoaderThread* mThread;
		void readNodes(TiXmlElement* Nodes, vector<NODE>& container );
		void readNode(TiXmlElement* Node, vector<NODE>& container );
	};
}
#endif
