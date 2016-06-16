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

// ����Unhandled Exception�Ļص�����     
//     
LONG DumpFile::ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	// ���ﵯ��һ������Ի����˳�����     
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


// ����Dump�ļ�     
void DumpFile::CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
	// ����Dump�ļ�     
	//     
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump��Ϣ     
	//     
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// д��Dump�ļ�����     
	//     
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}