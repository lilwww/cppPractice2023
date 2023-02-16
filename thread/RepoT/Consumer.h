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
