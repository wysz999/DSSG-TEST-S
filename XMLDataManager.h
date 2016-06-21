#ifndef _XMLDATAMANAGER_H_
#define _XMLDATAMANAGER_H_
/**********************

XML数据管理类

**********************/
//#include "common\common.h"
#include "common\common.h"
#include <string>
#include <map>
#include <mutex>
using namespace std;

#define SERVER_XML_INNER_MUTEX_NAME XML_inner_mutex
#define SERVER_XML_INNER_MUTEX std::mutex SERVER_XML_INNER_MUTEX_NAME;
#define SERVER_XML_INNER_LOCK std::unique_lock<std::mutex> serverXMLInnerMutexLock (SERVER_XML_INNER_MUTEX_NAME);

class XMLDataManager
{
public:
	XMLDataManager();
	//~XMLDataManager();

	//重新加载所有配置文件
	void ReLoadAll();

	//获取服务器配置
	uint32 getServerConfig(const string & _key);

private:
	SERVER_XML_INNER_MUTEX
	//服务器配置***********
	bool LoadServerConfig();
	bool ReLoadServerConfig();
	map<string, uint32> serverConfig;
	//********************
};



#endif // !_XMLDATAMANAGER_H_