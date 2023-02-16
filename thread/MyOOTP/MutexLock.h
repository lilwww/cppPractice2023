#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_
#include <pthread.h>
#include "NonCopyable.h"

class MutexLock
:public NonCopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void trylock();
    void unlock();
    pthread_mutex_t* getMutexLock();

private:
    pthread_mutex_t _mutex;

};

class MutexLockGuard{
private:
    MutexLock &_m;

public:
    MutexLockGuard(MutexLock&);
    ~MutexLockGuard();
};
#endif
