
#ifndef CXX_MAPSYNCOBJ_H
#	include "MapSyncObj.h"
#endif

MapSyncObj::MapSyncObj()
{
#ifdef WIN32
	::InitializeCriticalSection(&cs);
#else
 	pthread_mutexattr_init(&attr);
 	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
 	pthread_mutex_init(&mutex, &attr);
#endif
}

MapSyncObj::~MapSyncObj()
{
#ifdef WIN32
	::DeleteCriticalSection(&cs);
#else
 	pthread_mutexattr_destroy(&attr);
 	pthread_mutex_destroy(&mutex);
#endif
}

void
MapSyncObj::SyncStart()
{
#ifdef WIN32
	::EnterCriticalSection(&cs);
#else
	pthread_mutex_lock(&mutex);
#endif
}

bool
MapSyncObj::TrySyncStart()
{
#ifdef WIN32
	bool blRet = ::TryEnterCriticalSection(&cs);
	return blRet?true:false;
#else
    int ret = pthread_mutex_trylock(&mutex);
	return (ret==0)?true:false;
#endif
}

void
MapSyncObj::SyncEnd()
{
#ifdef WIN32
	::LeaveCriticalSection(&cs);
#else
	pthread_mutex_unlock(&mutex);
#endif
}
