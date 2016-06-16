#ifndef _COMMON_H_
#define _COMMON_H
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include "dump.h"


#include <string>


#include "tinyXML\tinyxml.h"



using namespace std;

TCHAR *char2tchar(char *str)
{
	int iLen = strlen(str);
	TCHAR *chRtn = new TCHAR[iLen + 1];
	mbstowcs(chRtn, str, iLen + 1);
	return chRtn;
}


#endif // !_COMMON_H_
