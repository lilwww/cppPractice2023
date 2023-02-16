#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

int main(int argc, char **argv)
{
    TaskQueue task(10);

    Producer pro(task);
    Producer con(task);
    // unique_ptr<Thread> con(new Consumer(task));

    task.startTh(pro.getTh());
    task.startTh(con.getTh());

    task.joinTh(pro.getTh());
    task.joinTh(con.getTh());

    return 0;
}
