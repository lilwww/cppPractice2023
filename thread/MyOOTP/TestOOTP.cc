#include "ThreadPool.h"
#include "Task.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;
using std::endl;
int processNum=0;
class MyTask
: public Task
{
public:
    void process() override
    {
        //此处写出具体做的业务逻辑
        ::srand(::clock());
        int number = ::rand() %100;
        cout<<"PROCESS NUM:" <<++processNum<<endl;
        cout << "Mytask produce number = " << number << endl;
    }
};

//1、任务执行不完(解决了，任务队列中的任务全部执行完毕)
//2、线程池有可能退不出来,但是任务执行完了
//
int main(int argc, char **argv)
{
    unique_ptr<Task> ptask(new MyTask());
    ThreadPool pool(4, 10);
    pool.start();
    size_t cnt = 20;

    while(cnt-- > 0)
    { 
        pool.addTask(ptask.get());
        cout << "cnt = " << cnt << endl;
    }

    pool.stop();
    return 0;
}


