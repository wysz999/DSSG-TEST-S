#include "Log.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "common\ServerLogicManager.h"
using namespace std;
void Log::Debug(char * title, char * format, ...)
{
	va_list argp;
	va_start(argp, format);
	char str[1024];
	dealchars(str,format, argp);
	if (strcmp(str,"\0") == 0)
	{
		return;
	}

	std::string s = c_out(title, str);

	write(s);

}

void Log::Error(char * title, char * format, ...)
{
	va_list argp;
	va_start(argp, format);
	char str[1024];
	dealchars(str, format, argp);
	if (strcmp(str, "\0") == 0)
	{
		return;
	}
	SERVER_LOG_INNER_LOCK
	std::string s = c_out(title, str,true);

	write(s);
}

char * Log::dealchars(char* str,char * format, va_list _ArgList)
{
	
//	auto i = _vscprintf(format, _ArgList);
	
	if (vsprintf(str, format, _ArgList) <= 0)
	{
		memset(str, 0, sizeof(str));
		return nullptr;
	}

	return str;
}

void Log::write(std::string str)
{
	static int i = 1;
	char buf[30];
	sprintf(buf, "log-[%s].log", sLM.getStringDataTime().c_str());
	fstream w;
	if (i == 1)
	{
		w.open(buf,  ofstream::out | ofstream::binary);
		--i;
	}
	else
	{
		w.open(buf, ofstream::app  | ofstream::binary);
	}
	
	if (!w.good())
	{
		w.close();
		return;
	}
	w << str;
	w.close();
}

std::string Log::c_out(char * title, char * format, bool isError)
{
	char buf[10];
	time_t ti = (time_t)time(0);
	tm localTime = *localtime(&ti);;
	strftime(buf, sizeof buf, "%R", &localTime);
	std::string str(buf);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY );
	cout << str << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	str += " ";
	if (isError)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED);
		cout << "E ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		str += "E ";
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "D ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		str += "D ";
	}
	cout << "[Log] ";
	str += "[Log] ";
	
	cout << title;
	str += title;

	cout << ": ";
	str += ": ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << format;
	str += format;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << '\n';
	str += '\n';
	return str;
}
