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
