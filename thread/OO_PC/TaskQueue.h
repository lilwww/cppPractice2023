#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;


class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    bool empty() const;
    bool full() const;
    void push(const int &value);
    int pop();

private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;//子对象
    Condition _notEmpty;
    Condition _notFull;
};

#endif
