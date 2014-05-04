#ifndef PLATFORM_THREAD_H
#define PLATFORM_THREAD_H

#ifdef WIN32
#   include <process.h>
#   include <windows.h>
    typedef HANDLE Handle;
#else
#   include <pthread.h>
    typedef pthread_t Handle;
#endif

namespace OgreSimple
{
    class PlatformThread
    {
    public:
        class Delegate {
        public:
            virtual void ThreadMain() = 0;

        protected:
            virtual ~Delegate() {}
        };

        static bool Create(Delegate* delegate, Handle* handle);
        static void Join(Handle handle);
    };
}
#endif
