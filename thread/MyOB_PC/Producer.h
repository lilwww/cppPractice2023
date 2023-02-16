#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "Thread.h"
#include "TaskQueue.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <functional>

using std::bind;
using std::cout;
using std::endl;
class Producer
{
public:
    Producer(TaskQueue &taskQue)
        : _taskQue(taskQue), _th(bind(&Producer::run, this))
    {
    }

    ~Producer()
    {
    }

    Thread &getTh()
    {
        return _th;
    }
    void run()
    {
        setThFunc();
        // 连续生产不一样的数据(目的就是为了产生随机值)
        ::srand(::clock()); // 种种子
        size_t cnt = 20;
        while (cnt-- > 0)
        {
            int number = ::rand() % 1000;
            _taskQue.push(number, _th);
            cout << ">>Producer produce: " << number << endl;
            sleep(1);
        }
    }
    void setThFunc()
    {
        //_th = Thread(bind(&Producer::run, this));
    }

private:
    TaskQueue &_taskQue;
    Thread _th;
};

#endif
