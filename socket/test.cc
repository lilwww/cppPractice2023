#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

void *threadFunc(void *)
{

}

void test()
{
    pthread_t thid[40000];
    for(size_t idx = 0; idx != 30000; ++idx)
    {
        pthread_create(&thid[idx], nullptr, threadFunc, nullptr);
    }
    while(1);
}

int main(int argc, char **argv)
{
    test();
    return 0;
}

