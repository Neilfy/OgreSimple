#include "ThreadBase.h"

namespace OgreSimple
{
    ThreadBase::ThreadBase()
        : mHandle(0)
        , mIsRun(false)
    {}

    ThreadBase::~ThreadBase()
    {
        Stop();
    }

    bool ThreadBase::Start()
    {
        bool success = PlatformThread::Create(this, &mHandle);
        return success;
    }

    void ThreadBase::Stop()
    {
        mIsRun = false;
    }

    void ThreadBase::ThreadMain()
    {
        mIsRun = true;
        while(mIsRun)
        {
            DoWork();
        }
    }
}
