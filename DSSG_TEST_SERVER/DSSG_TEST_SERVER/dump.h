#ifndef _DUMP_H_
#define _DUMP_H_

#include <Windows.h>  
#pragma comment( lib, "dbghelp" )
class DumpFile
{
public:
	DumpFile(void);
	~DumpFile(void);

	static void StartDump(TCHAR* filename);

	static void test() { int i = 0; i = i / i; }
	void test2();
protected:
	static TCHAR DumpFileName[1024];
	static LONG DumpFile::ApplicationCrashHandler(EXCEPTION_POINTERS *pException);
	static void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);

};


#endif // !_DUMP_H_
