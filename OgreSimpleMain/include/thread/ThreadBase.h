#ifndef THREADBASE_H
#define THREADBASE_H

#include "platform_thread.h"

namespace OgreSimple
{
    class ThreadBase : public PlatformThread::Delegate
    {
    public:
        ThreadBase();
        virtual ~ThreadBase();
        bool Start();
        void Stop();
        void StopSoon();
        virtual void ThreadMain();
        virtual void DoWork() = 0;

    private:
        Handle mHandle;
        bool mIsRun;
    }; 
}
#endif
