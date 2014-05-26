#ifndef CXX_MAPSYNCOBJ_H
#define CXX_MAPSYNCOBJ_H

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

class MapSyncObj
{
public:
	MapSyncObj();
	virtual ~MapSyncObj();

	void    SyncStart();
	bool    TrySyncStart();
	void    SyncEnd();

protected:

#ifdef WIN32
    CRITICAL_SECTION cs;
#else
 	pthread_mutex_t mutex;
 	pthread_mutexattr_t attr;
#endif

private:
	MapSyncObj(const MapSyncObj& src){}
	MapSyncObj& operator = (const MapSyncObj& src){return *this;}
};

#endif
