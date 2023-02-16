#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include <memory>
#include <vector>
#include "Thread.h"
#include "TaskQueue.h"
class ThreadPool
{
    friend class WorkThread;
public:
    ThreadPool(size_t,size_t);
    ~ThreadPool();
    void addTask(ElemTy);
    void start();
    void stop();    
private:
    ElemTy getTask();
    void threadFunc();
private:
    size_t _thNum;
    size_t _tqSize;
    bool _isExit;
    TaskQueue _taskQ;
    std::vector<std::unique_ptr<Thread>> _threads;    

};
#endif
