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

