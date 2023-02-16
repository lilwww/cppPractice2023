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
