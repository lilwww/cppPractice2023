#ifndef __MUTEXLOKC_H__
#define __MUTEXLOKC_H__

#include <pthread.h>

class MutexLock
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    void trylock();

    pthread_mutex_t *getMutexLockPtr()
    {
        return &_mutex;
    }

private:
    pthread_mutex_t _mutex;
};

#endif
