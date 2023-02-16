#include "MutexLock.h"
#include "Condition.h"
#include <stdio.h>

Condition::Condition(MutexLock &mutex)
: _mutex(mutex)
{
    int ret = pthread_cond_init(&_cond, nullptr);
    if(ret)
    {
        perror("pthread_cond_init\n");
        return;
    }
}

Condition::~Condition()
{
    int ret = pthread_cond_destroy(&_cond);
    if(ret)
    {
        perror("pthread_cond_destroy\n");
        return;
    }
}

void Condition::wait()
{
    //有可能报MutexLock是不完整类型,需要加上头文件
    int ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
    if(ret)
    {
        perror("pthread_cond_wait\n");
        return;
    }
}

void Condition::notify()
{
    int ret = pthread_cond_signal(&_cond);
    if(ret)
    {
        perror("pthread_cond_signal\n");
        return;
    }
}

void Condition::notifyAll()
{
    int ret = pthread_cond_broadcast(&_cond);
    if(ret)
    {
        perror("pthread_cond_broadcast\n");
        return;
    }
}
#include "MutexLock.h"
#include <stdio.h>

MutexLock::MutexLock()
{
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if(ret)
    {
        perror("pthread_mutex_init\n");
        return;
    }
}

MutexLock::~MutexLock()
{
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_destroy\n");
        return;
    }
}

void MutexLock::lock()
{
    int ret = pthread_mutex_lock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_lock\n");
        return;
    }
}

void MutexLock::unlock()
{
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_unlock\n");
        return;
    }
}

void MutexLock::trylock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_trylock\n");
        return;
    }
}
#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
{

}

TaskQueue::~TaskQueue()
{

}

bool TaskQueue::empty() const
{
    return 0 == _que.size();
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

void TaskQueue::push(const int &value)
{
    //访问共享资源，需要先上锁
    _mutex.lock();

    if(full())
    {
        _notFull.wait();//让生产者等待在条件变量上
    }

    _que.push(value);

    _notEmpty.notify();//唤醒消费者

    //为了防止死锁，所以需要解锁
    _mutex.unlock();
}

int TaskQueue::pop()
{
    //访问共享资源，需要先上锁
    _mutex.lock();

    if(empty())
    {
        _notEmpty.wait();//让消费者处于睡眠状态
    }
    

    //获取queue中的第一个元素，使用front()
    //还要将元素删除，使用pop()
    int tmp = _que.front();
    _que.pop();

    _notFull.notify();//唤醒生产者
    
    //为了防止死锁，所以需要解锁
    _mutex.unlock();

    return tmp;

}
#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test()
{
    //创建的栈对象
    TaskQueue task(10);
    Producer pro(task);
    Consumer con(task);

    pro.start();
    con.start();

    pro.join();
    con.join();
}

int main(int argc, char **argv)
{
    TaskQueue task(10);

    unique_ptr<Thread> pro(new Producer(task));
    unique_ptr<Thread> con(new Consumer(task));

    pro->start();
    con->start();

    pro->join();
    con->join();

    return 0;
}

#include "Thread.h"
#include <stdio.h>

Thread::Thread()
: _thid(0)
, _isRunning(false)
{
}

Thread::~Thread()
{
    if(_isRunning)
    {
        //让子线程与主线程分离，主线程不管子线程的回收
        pthread_detach(_thid);
        _isRunning = false;
    }
}

//线程启动函数
//this指针指向的是pth，指向的是new MyThread
void Thread::start()
{
    //1、threadFunc是一个成员函数，所以需要消除this指针影响
    //2、pthread_create第四个参数不能设置为空，不然在threadFunc
    //中没有对象去调用run方法,所以第四个参数需要传递对象进来
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        perror("pthread_create\n");
        return;
    }

    _isRunning = true;
}

void Thread::join()
{
    if(_isRunning)
    {
        //shift + k(2, 3)
        int ret = pthread_join(_thid, nullptr);
        if(ret)
        {
            perror("pthread_join\n");
            return;
        }

        _isRunning = false;
    }
}

//静态成员函数
void *Thread::threadFunc(void *arg)
{
    Thread *pth1 = static_cast<Thread *>(arg);
    if(pth1)
    {
        //为了防止threadFunc没有this指针，所以可以在pthread_create
        //中作为参数传进来
        pth1->run();//体现多态
    }

    //让子线程主动退出
    pthread_exit(nullptr);
}

