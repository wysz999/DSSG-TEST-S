#include "stdafx.h"
#include "dump.h"  
#include <DbgHelp.h>  

void DumpFile::StartDump(TCHAR* filename)
{
	_tcscpy(DumpFileName, filename);
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}

void DumpFile::test2()
{
	int i = 0;
}

// 处理Unhandled Exception的回调函数     
//     
LONG DumpFile::ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	// 这里弹出一个错误对话框并退出程序     
	//     
	//  FatalAppExit(-1,  _T("*** Unhandled Exception! ***"));    

	CreateDumpFile(DumpFileName, pException);
	return EXCEPTION_EXECUTE_HANDLER;
}

TCHAR DumpFile::DumpFileName[1024];

DumpFile::DumpFile(void)
{

}

DumpFile::~DumpFile(void)
{
}


// 创建Dump文件     
void DumpFile::CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
	// 创建Dump文件     
	//     
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump信息     
	//     
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// 写入Dump文件内容     
	//     
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}