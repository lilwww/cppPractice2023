#include "ThreadPool.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;
using std::endl;

class MyTask
{
public:
    void process() 
    {
        //此处写出具体做的业务逻辑
        ::srand(::clock());
        int number = ::rand() %100;
        cout << "BO_ThreadPool...Mytask produce number = " << number << endl;
    }
};

int main(int argc, char **argv)
{
    //创建MyTask对象
    /* MyTask task;//栈对象 */
    unique_ptr<MyTask> ptask(new MyTask());//堆对象
    ThreadPool pool(4, 10);
    pool.start();

    size_t cnt = 20;
    while(cnt-- > 0)
    {
        /* pool.addTask(std::bind(&MyTask::process, &task)); */
        pool.addTask(std::bind(&MyTask::process, ptask.get()));
        cout << "cnt = " << cnt << endl;
    }

    pool.stop();
    return 0;
}

