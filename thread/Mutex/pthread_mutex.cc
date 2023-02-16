#include <string.h>
#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

#define  ERROR_CHECK(msg, ret) \
    do{                 \
        printf("%s: %s\n", msg, strerror(ret)); \
    }while(0);

void test()
{
    pthread_mutex_t mutex;
    int ret = pthread_mutex_init(&mutex, nullptr);
    ERROR_CHECK("pthread_mutex_init", ret);
    //...
    //...逻辑代码使用锁

    ret = pthread_mutex_destroy(&mutex);
    ERROR_CHECK("pthread_mutex_destroy", ret);
}

int main(int argc, char **argv)
{
    test();
    return 0;
}

