#include "common\common.h"
#include "dump.h"
#include "common\Timer.h"
#include "Main_init.h"

using namespace std;

void test(char *b, ...)
{
	char a[256];
	va_list argp;
//	char * para;

	va_start(argp, b);
	auto s = _vscprintf(b, argp);
	a[s + 1] = '\n';
	vsprintf(a,b, argp);
	 
	//auto temp = va_arg(para, void*);

	va_end(argp);
	cout << a << endl;
}


int main(int argc, char* argv[])
{
	//注册单例
	register_singleton();

	char buf[30];

	sprintf(buf, "core[%s-%s].dmp", sLM.getStringDataTime().c_str(), sLM.getStringTimer().c_str());

	DumpFile::StartDump(sLM.char2tchar(buf));

	LOG.Debug("test", "123");
	LOG.Error("test", "%d",233333);


	unsigned count = 1; // 至少一个  
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	count = si.dwNumberOfProcessors;

	cout << "cpu" << count << endl;
	return 0;
}