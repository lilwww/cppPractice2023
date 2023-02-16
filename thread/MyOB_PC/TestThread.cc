#include "Thread.h"
#include <unistd.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
{
public:
    void process() 
    {
        //process方法中具体的实现逻辑可以根据具体的
        //业务场景进行书写
        while(1)
        {
            cout << "MyTask is isRunning!" << endl;
            sleep(1);
        }
    }
};

void func(int x)
{
    while(1)
    {
        cout << "Func is isRunning!" << endl;
        sleep(x);
    }

}

void test()
{
    MyTask task;
    Thread th(std::bind(&MyTask::process, &task));

    th.start();
    th.join();
}

void test2()
{
    MyTask task;
    function<void()> f = std::bind(&MyTask::process, &task);
    Thread th(std::move(f));

    th.start();
    th.join();
}

void test3()
{
    MyTask task;
    /* function<void()> f = std::bind(&MyTask::process, &task); */

    /* unique_ptr<Thread> pth(new Thread(std::move(f))); */
    unique_ptr<Thread> 
        pth(new Thread(std::bind(&MyTask::process, &task)));

    pth->start();
    pth->join();
}

void test4()
{
    /* unique_ptr<Thread> pth(new Thread(std::move(func))); */
    /* unique_ptr<Thread> pth(new Thread(std::bind(func))); */
    unique_ptr<Thread> pth(new Thread(std::bind(&func, 2)));

    pth->start();
    pth->join();
}



