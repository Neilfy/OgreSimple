#include "platform_thread.h"

namespace OgreSimple
{
    struct ThreadParams
    {
        PlatformThread::Delegate* delegate;
    };

    unsigned int __stdcall ThreadFunc(void* params)
    {
        ThreadParams* thread_params = static_cast<ThreadParams*>(params);
        PlatformThread::Delegate* delegate = thread_params->delegate;
        delegate->ThreadMain();
        _endthreadex(0);
        return 0;
    }

    bool PlatformThread::Create(Delegate* delegate, Handle* handle)
    {
        ThreadParams params;
        params.delegate = delegate;
        Handle thread_handle = (Handle)_beginthreadex(NULL, 0, ThreadFunc, &params, 0, NULL);
        *handle = thread_handle;
        Sleep(1000);
        return true;
    }

    void PlatformThread::Join(Handle handle)
    {
        WaitForSingleObject(handle, INFINITE);
        CloseHandle(handle);
    }
}
