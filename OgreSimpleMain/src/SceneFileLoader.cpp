#include "SceneFileLoader.h"
#include "ResourcesLoaderThread.h"
#include<sstream>
namespace OgreSimple
{
	SceneFileLoader::SceneFileLoader(ResourcesLoaderThread *worker):
		mThread(worker)
	{

	}
	void SceneFileLoader::readNode(TiXmlElement* Node, vector<NODE>& container)
	{
		string val;
		NODE info;
		TiXmlElement* subNode=0;
		info.name = Node->Attribute("name");
		string type = Node->Attribute("type");
		if(type == "model")
			info.type = 1;
		else if(type == "box")
			info.type = 2;

		for( subNode = Node->FirstChildElement(); subNode; subNode = subNode->NextSiblingElement() )
		{
			val = subNode->Value();
			if (val == "Mesh")
			{
				info.mesh = subNode->FirstChild()->Value();
			}

			if (val == "Position")
			{
				string pos = subNode->FirstChild()->Value();
				vector<string> vecOut;
				splitString(pos, ",", vecOut);
				info.position.x = parseFloat(vecOut[0]);
				info.position.y = parseFloat(vecOut[1]);
				info.position.z = parseFloat(vecOut[2]);
			}

			if (val == "Scale")
			{
				string scale = subNode->FirstChild()->Value();
				vector<string> vecOut;
				splitString(scale, ",", vecOut);
				info.scale.x = parseFloat(vecOut[0]);
				info.scale.y = parseFloat(vecOut[1]);
				info.scale.z = parseFloat(vecOut[2]);
			}

			if (val == "size")
			{
				string pos = subNode->FirstChild()->Value();
				vector<string> vecOut;
				splitString(pos, ",", vecOut);
				info.size.x = parseFloat(vecOut[0]);
				info.size.y = parseFloat(vecOut[1]);
				info.size.z = parseFloat(vecOut[2]);
			}

			if (val == "texture")
			{
				info.texture = subNode->FirstChild()->Value();
			}

			if (val == "Nodes")
			{
				readNodes(subNode,info.nodes);
			}
		}

		container.push_back(info);
	}
	void SceneFileLoader::readNodes(TiXmlElement* Nodes, vector<NODE>& container )
	{
		TiXmlElement* Node=0;
		string val;
		for( Node = Nodes->FirstChildElement(); Node; Node = Node->NextSiblingElement() )
		{
			val = Node->Value();
			if (val == "Node")
			{
				readNode(Node,container);
			}

		}
	}
	void SceneFileLoader::loadFile(string path)
	{
		try
		{

			//创建一个XML的文档对象。
			TiXmlDocument *myDocument = new TiXmlDocument(path.c_str());
			myDocument->LoadFile();
			//获得根元素，即Persons。
			TiXmlElement *RootElement = myDocument->RootElement();

			string val = RootElement->Value();
			if (RootElement && val == "Nodes")
			{
				readNodes(RootElement,m_Nodes);
			}

			createEntitys(m_Nodes);

			delete myDocument;

		}
		catch (string& e)
		{

		}
	}

	void SceneFileLoader::createEntitys(vector<NODE>& nodes)
	{
		vector<NODE>::iterator it,it_end;
		it_end = nodes.end();
		for (it=nodes.begin(); it != it_end; ++it)
		{
			ResourceInfo task_info = {
                it->name,
                it->mesh,
				it->type,
				it->size,
				it->texture,
				it->position,
				it->scale
			};

			mThread->addTask(task_info);
			if(it->nodes.size() != 0)
			{
				createEntitys(it->nodes);
			}
		}


	}

	void SceneFileLoader::splitString(const string& src, const string& tok, vector<string>& vecStrOut)
	{
		string::size_type last_pos = 0;
		string::size_type pos = 0;

		while(true)
		{
			pos = src.find_first_of(tok, last_pos);
			if( pos == string::npos )
			{
				vecStrOut.push_back(src.substr(last_pos));
				break;
			}
			else
			{
				vecStrOut.push_back(src.substr(last_pos, pos - last_pos));
				last_pos = pos + 1;
			}
		}

	}

	float SceneFileLoader::parseFloat(const string& val)
	{
		// Use istringstream for direct correspondence with toString
		std::istringstream str(val);
		float ret = 0;
		str >> ret;

		return ret;
	}

}
