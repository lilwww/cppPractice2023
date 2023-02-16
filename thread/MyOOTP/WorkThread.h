#ifndef _WORKTHREAD_H_
#define _WORKTHREAD_H_
#include "Thread.h"
#include "ThreadPool.h"
class WorkThread
:public Thread
{
public:
    WorkThread(ThreadPool& p):_pool(p) {}
    ~WorkThread() {}
    void run() override{
        _pool.threadFunc();
    }
private:
    ThreadPool& _pool;
};
#endif
