#ifndef _CONDITION_H_
#define _CONDITION_H_
#include <pthread.h>
#include "MutexLock.h"
#include "NonCopyable.h"
class Condition
:NonCopyable
{
public:
    Condition(MutexLock &);
    ~Condition();
    void wait();
    void notify();
    void notifyAll();
private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};
#endif
