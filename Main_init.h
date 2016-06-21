#ifndef _MAIN_INIT_H_
#define _MAIN_INIT_H__
#include "common\ServerLogicManager.h"
#include "Log.h"
#include "ThreadPool.h"
#include "XMLDataManager.h"
initialiseSingleton(serverLogicManager);
initialiseSingleton(Log);
initialiseSingleton(ThreadPool);
initialiseSingleton(XMLDataManager);
void register_singleton()
{
	createFileSingleton(serverLogicManager);
	createFileSingleton(Log);
	createFileSingleton(ThreadPool);
	createFileSingleton(XMLDataManager);
}


#endif // !_MAIN_INIT_H_
