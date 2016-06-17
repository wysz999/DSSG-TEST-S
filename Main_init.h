#ifndef _MAIN_INIT_H_
#define _MAIN_INIT_H__
#include "common\ServerLogicManager.h"
#include "Log.h"
initialiseSingleton(serverLogicManager);
initialiseSingleton(Log);
void register_singleton()
{
	createFileSingleton(serverLogicManager);
	createFileSingleton(Log);
}


#endif // !_MAIN_INIT_H_
