#ifndef __CONSUMER_H__
#define __CONSUMER_H__

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

class Consumer
{
public:
    Consumer(TaskQueue &taskQue)
        : _taskQue(taskQue), _th(bind(&Consumer::run, this))
    {
    }

    ~Consumer()
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
        size_t cnt = 20;
        while (cnt-- > 0)
        {
            int number = _taskQue.pop(_th);
            // 原子操作
            cout << ">>Consumer consume : " << number << endl;
            sleep(1);
        }
    }
    void setThFunc()
    {
        //_th = Thread(bind(&run, this));
    }

private:
    TaskQueue &_taskQue;
    Thread _th;
};

#endif
