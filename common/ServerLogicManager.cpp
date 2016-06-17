#include "ServerLogicManager.h"
#include <time.h>
#include <iostream>
#include <string>
using namespace std;
uint32 serverLogicManager::getDataTime(uint32 time)
{
	if (time == 0)
	{
		time = ::time(0);
	}
	time_t ti = (time_t)time;
	tm localTime = *localtime(&ti);
	char buf[20];
	strftime(buf, sizeof buf, "%Y%m%d", &localTime);
	string t(buf);
	return stoi(t);
}

uint32 serverLogicManager::getTimer(uint32 time)
{
	if (time == 0)
	{
		time = ::time(0);
	}
	time_t ti = (time_t)time;
	tm localTime = *localtime(&ti);
	char buf[20];
	strftime(buf, sizeof buf, "%H%M%S", &localTime);
	string t(buf);
	return stoi(t);
}

string serverLogicManager::getStringDataTime(uint32 time)
{
	if (time == 0)
	{
		time = ::time(0);
	}
	time_t ti = (time_t)time;
	tm localTime = *localtime(&ti);
	char buf[20];
	strftime(buf, sizeof buf, "%Y-%m-%d", &localTime);

	return buf;
}

string serverLogicManager::getStringTimer(uint32 time)
{
	if (time == 0)
	{
		time = ::time(0);
	}
	time_t ti = (time_t)time;
	tm localTime = *localtime(&ti);
	char buf[20];
	strftime(buf, sizeof buf, "%H-%M-%S", &localTime);
	return buf;
}

TCHAR * serverLogicManager::char2tchar(char * str)
{
	int iLen = strlen(str);
	TCHAR *chRtn = new TCHAR[iLen + 1];
	mbstowcs(chRtn, str, iLen + 1);
	return chRtn;
}
