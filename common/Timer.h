#ifndef WGS_TIMER_H
#define WGS_TIMER_H
#include <Windows.h>
#include "common.h"
#ifdef WIN32
__forceinline uint32 getMSTime() { return GetTickCount(); }
#else
WGSERVER_INLINE uint32 getMSTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
#endif

#endif


