#ifndef _LOG_H_
#define _LOG_H_
/**********************

��־�����

**********************/
#include "common\Singleton.h"
#include <stdio.h>
#include <mutex>
#include <string>
#define SERVER_LOG_INNER_MUTEX_NAME log_inner_mutex
#define SERVER_LOG_INNER_MUTEX std::mutex SERVER_LOG_INNER_MUTEX_NAME;
#define SERVER_LOG_INNER_LOCK std::unique_lock<std::mutex> serverLogInnerMutexLock (SERVER_LOG_INNER_MUTEX_NAME);
class Log: public Singleton<Log>
{
	SERVER_LOG_INNER_MUTEX
public:
	//��ӡdebug��Ϣ����¼
	void Debug(char*  title, char*  format, ...);
	//��ӡ������Ϣ����¼
	void Error(char*  title, char*  format, ...);
private:
	char* dealchars(char* str, char* format, va_list _ArgList);
	void write(std::string str);
	std::string c_out(char* title, char * format, bool isError = false);
};
#define LOG Log::getSingleton()  
#endif // !_LOG_H_