#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_
#include <string>
using namespace std;

class ThreadBase
{
public:
	ThreadBase();
	~ThreadBase();
	string _threadName;
	inline const string & getThreadName() { return _threadName; }
	inline void setThreadName(const string & name) { _threadName = name; }
	virtual void run() = 0;
};


#endif // !_THREAD_BASE_H_

