#ifndef _TASKQUEUE_H_
#define _TASKQUEUE_H_
#include <queue>
#include <memory>
#include "Task.h"
#include "MutexLock.h"
#include "Condition.h"

using std::unique_ptr;
using ElemTy= Task*;
class TaskQueue
{
public:
    TaskQueue(size_t);
    ~TaskQueue();
    ElemTy pop();
    void push(ElemTy);
    bool isEmpty() const;
    bool isFull() const;
    void wakeup();
private:
    size_t queSize;
    std:: queue<ElemTy> taskQ;
    bool notExit;
    MutexLock _mutex;
    Condition notEmpty;
    Condition notFull;
    
};
#endif
