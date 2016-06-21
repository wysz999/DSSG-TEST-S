#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include "common\Singleton.h"
#include "common\ThreadBase.h"
#include "common\ServerEnum.h"
#include "common\common.h"
typedef struct
{
	//�߼�
	ThreadBase* _thread;
	//״̬
	TheadState _theadState;

}ServerThead;

class ThreadPool:public Singleton<ThreadPool>
{
public:
	ThreadPool();
	~ThreadPool();
	//�ͷſ����̼߳��ʱ�� 
	uint32 checkFreeTime;
};

#define THEAD_P ThreadPool::getSingleton() 

#endif // !_THREAD_POOL_H_


