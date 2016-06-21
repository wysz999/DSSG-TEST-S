#include "XMLDataManager.h"
#include "Log.h"
#include "common\tinyXML\tinyxml.h"
XMLDataManager::XMLDataManager()
{
	LoadServerConfig();
}

uint32 XMLDataManager::getServerConfig(const string & _key)
{
	SERVER_XML_INNER_LOCK
	map<string, uint32>::iterator iter = serverConfig.find(_key);
	if (iter != serverConfig.end())
	{
		return (*iter).second;
	}
	LOG.Error("XMLDataManager::getServerConfig", "not find key: %s", _key.c_str());
	return uint32(65535);
}

bool XMLDataManager::LoadServerConfig()
{
	TiXmlDocument doc("Server_XML/ServerConfig.xml");
	if (!doc.LoadFile())
	{
		LOG.Error(" XMLDataManager::LoadServerConfig()", "Load Server_XML/ServerConfig.xml failed!");
		return false;
	}
	TiXmlElement* pRoot = doc.RootElement();

	
	while (nullptr != pRoot)
	{
		string _key = pRoot->Attribute("name");
		uint32 _value = stoul(pRoot->Attribute("value"));
		serverConfig.insert(std::make_pair(_key,_value));
		pRoot = pRoot->NextSiblingElement();
	}
	LOG.Debug(" XMLDataManager::LoadServerConfig()", "Load Server_XML/ServerConfig.xml successfully!");
	return true;
}

bool XMLDataManager::ReLoadServerConfig()
{
	SERVER_XML_INNER_LOCK
	serverConfig.clear();
	LoadServerConfig();
	return true;
}
