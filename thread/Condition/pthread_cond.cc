#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

#define  ERROR_CHECK(msg, ret) \
    do{                 \
        printf("%s: %s\n", msg, strerror(ret)); \
    }while(0);

typedef struct
{
    int num;//添加一个数据
    pthread_mutex_t mutex;//互斥锁
    pthread_cond_t cond;//条件变量
}Data_t;

//让主线程发通知，让子线程进行等待，然后主线程唤醒子线程
void *threadFunc(void *arg)
{
    Data_t *pData = (Data_t *)arg;
    int ret = pthread_mutex_lock(&pData->mutex);
    ERROR_CHECK("pthread_mutex_lock2", ret);

    //该函数会分为两个部分
    //1、上半部：（在条件变量上）排队；解锁；睡眠；
    //2、下半部：(从条件变量上)被唤醒；加锁；函数返回
    ret = pthread_cond_wait(&pData->cond, &pData->mutex);
    ERROR_CHECK("pthread_cond_wait", ret);

    ret = pthread_mutex_unlock(&pData->mutex);
    ERROR_CHECK("pthread_mutex_unlock2", ret);

    pthread_exit(nullptr);
}

int main(int argc, char **argv)
{
    Data_t data;
    data.num = 0;

    //互斥锁初始化
    int ret = pthread_mutex_init(&data.mutex, nullptr);
    ERROR_CHECK("pthread_mutex_init", ret);

    //条件变量的初始化
    ret = pthread_cond_init(&data.cond, nullptr);
    ERROR_CHECK("pthread_cond_init", ret);

    //创建子线程，让其等待在条件变量上
    pthread_t thid;
    ret = pthread_create(&thid, nullptr, threadFunc, &data);
    ERROR_CHECK("pthread_create", ret);

    //添加时间的目的，就是为了将CPU的控制权发出来，让子线程
    //可以先于主线程执行
    //(如果要完全控制时序，保证每一次都一样，需要让一方主动
    //放弃对CPU的控制权)
    usleep(10);

    //互斥锁加锁
    ret = pthread_mutex_lock(&data.mutex);
    ERROR_CHECK("pthread_mutex_lock1", ret);

    //主线程发通知给子线程，让子线程从等待状态被唤醒
    ret = pthread_cond_signal(&data.cond);
    ERROR_CHECK("pthread_cond_signal", ret);

    //互斥锁解锁
    ret = pthread_mutex_unlock(&data.mutex);
    ERROR_CHECK("pthread_mutex_unlock1", ret);

    //主线程要等待子线程的退出，然后回收子线程的资源
    ret = pthread_join(thid, nullptr);
    ERROR_CHECK("pthread_join", ret);

    //互斥锁的销毁
    ret = pthread_mutex_destroy(&data.mutex);
    ERROR_CHECK("pthread_mutex_destroy", ret);

    //条件变量的销毁
    ret = pthread_cond_destroy(&data.cond);
    ERROR_CHECK("pthread_cond_destroy", ret);
    return 0;
}

