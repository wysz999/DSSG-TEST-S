#ifndef _SERVER_LOGIC_MANAGER_H_
#define _SERVER_LOGIC_MANAGER_H_
/**********************

服务器逻辑

**********************/

#include "Singleton.h"
#include "Timer.h"
#include <string>

#define SERVER_sLM_INNER_MUTEX_NAME sLM_inner_mutex
#define SERVER_sLM_INNER_MUTEX std::mutex SERVER_sLM_INNER_MUTEX_NAME;
#define SERVER_sLM_INNER_LOCK std::unique_lock<std::mutex> serversLMInnerMutexLock (SERVER_sLM_INNER_MUTEX_NAME);

class serverLogicManager :public Singleton <serverLogicManager >
{
public:
	//根据时间戳获取年月日信息，参数默认为当前时间
	//uint32 time    时间戳
	//返回值20160617
	uint32 getDataTime(uint32 time = 0);

	//根据时间戳获取时分秒信息，参数默认为当前时间
	//uint32 time    时间戳
	//返回值154501
	uint32 getTimer(uint32 time = 0);

	//根据时间戳获取年月日信息，参数默认为当前时间
	//uint32 time    时间戳
	//返回值2016-06-17
	std::string getStringDataTime(uint32 time = 0);

	//根据时间戳获取时分秒信息，参数默认为当前时间
	//uint32 time    时间戳
	//返回值15-45-01
	std::string getStringTimer(uint32 time = 0);

	//输入char 转换 tchar
	//char *str  待转换字符串
	TCHAR *char2tchar(char *str);
};
#define sLM serverLogicManager::getSingleton()
#endif // ! _SERVER_LOGIC_MANAGER_H_
