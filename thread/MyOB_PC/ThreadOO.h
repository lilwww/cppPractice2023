#ifndef __THREADOO_H__
#define __THREADOO_H__

#include <pthread.h>

class ThreadOO
{
public:
    ThreadOO();
    virtual ~ThreadOO();

    //线程的开始与结束
    void start();
    void join();

private:
    //线程入口函数
    static void *threadFunc(void *arg);
    //线程的执行任务
    virtual void run() = 0;

private:
    pthread_t _thid;//线程id
    bool _isRunning;//线程运行的标志
};

#endif