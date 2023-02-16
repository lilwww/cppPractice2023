#include "Thread.h"
#include <unistd.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread
: public Thread
{
/* public: */
private:
    void run() override
    {
        //run方法中具体的实现逻辑可以根据具体的业务场景进行书写
        while(1)
        {
            cout << "MyThread is isRunning!" << endl;
            sleep(1);
        }
    }
};

int main(int argc, char **argv)
{
    /* MyThread th; */
    /* th.start(); */
    /* th.run(); */
    /* th.join(); */

    /* Thread *pth = new MyThread(); */
    unique_ptr<Thread> pth(new MyThread());
    pth->start();
    pth->join();

    return 0;
}

