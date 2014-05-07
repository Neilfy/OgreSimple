#include "platform_thread.h"
#include <pthread.h>

namespace OgreSimple
{
    struct ThreadParams
    {
        PlatformThread::Delegate* delegate;
    };

    void* ThreadFunc(void* params)
    {
        //ThreadParams* thread_params = static_cast<ThreadParams*>(params);
        PlatformThread::Delegate* delegate = static_cast<PlatformThread::Delegate*>(params);//thread_params->delegate;
        delegate->ThreadMain();
        return NULL; 
    }

    bool PlatformThread::Create(Delegate* delegate, Handle* handle)
    {
        ThreadParams params;
        params.delegate = delegate;
        
        int err = pthread_create(handle, NULL, OgreSimple::ThreadFunc, delegate);//if OK return 0
        return !err; 
    }

    void PlatformThread::Join(Handle handle)
    {
        pthread_join(handle, NULL);
    } 
}
