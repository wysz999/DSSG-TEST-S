#ifndef _SERVER_LOGIC_MANAGER_H_
#define _SERVER_LOGIC_MANAGER_H_
/**********************

�������߼�

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
	//����ʱ�����ȡ��������Ϣ������Ĭ��Ϊ��ǰʱ��
	//uint32 time    ʱ���
	//����ֵ20160617
	uint32 getDataTime(uint32 time = 0);

	//����ʱ�����ȡʱ������Ϣ������Ĭ��Ϊ��ǰʱ��
	//uint32 time    ʱ���
	//����ֵ154501
	uint32 getTimer(uint32 time = 0);

	//����ʱ�����ȡ��������Ϣ������Ĭ��Ϊ��ǰʱ��
	//uint32 time    ʱ���
	//����ֵ2016-06-17
	std::string getStringDataTime(uint32 time = 0);

	//����ʱ�����ȡʱ������Ϣ������Ĭ��Ϊ��ǰʱ��
	//uint32 time    ʱ���
	//����ֵ15-45-01
	std::string getStringTimer(uint32 time = 0);

	//����char ת�� tchar
	//char *str  ��ת���ַ���
	TCHAR *char2tchar(char *str);
};
#define sLM serverLogicManager::getSingleton()
#endif // ! _SERVER_LOGIC_MANAGER_H_
