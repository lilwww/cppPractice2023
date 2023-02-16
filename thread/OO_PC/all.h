#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>

//前向声明
class MutexLock;

class Condition
{
public:
    Condition(MutexLock &mutex);
    ~Condition();
    void wait();
    void notify();
    void notifyAll();

private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};

#endif
#ifndef __CONSUMER_H__
#define __CONSUMER_H__


#include "Thread.h"
#include "TaskQueue.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;

class Consumer
: public Thread
{
public:
    Consumer(TaskQueue &taskQue)
    : _taskQue(taskQue)
    {

    }

    ~Consumer()
    {

    }

    void run() override
    {
        //连续生产不一样的数据(目的就是为了产生随机值)
        size_t cnt = 20;
        while(cnt-- > 0)
        {
            int number = _taskQue.pop();
            //原子操作
            cout << ">>Consumer consume : " << number << endl;
            sleep(1);
        }
    }

private:
    TaskQueue &_taskQue;
};

#endif
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
#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "Thread.h"
#include "TaskQueue.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

class Producer
: public Thread
{
public:
    Producer(TaskQueue &taskQue)
    : _taskQue(taskQue)
    {

    }

    ~Producer()
    {

    }

    void run() override
    {
        //连续生产不一样的数据(目的就是为了产生随机值)
        ::srand(::clock());//种种子
        size_t cnt = 20;
        while(cnt-- > 0)
        {
            int number = ::rand() % 1000;
            _taskQue.push(number);
            cout << ">>Producer produce: " << number << endl;
            sleep(1);
        }
    }

private:
    TaskQueue &_taskQue;
};

#endif
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
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread
{
public:
    Thread();
    virtual ~Thread();

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
