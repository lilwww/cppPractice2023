#ifndef _THREAD_H_
#define _THREAD_H_
#include <pthread.h>
class Thread
{
public:
    Thread();
    virtual ~Thread();
    void start();
    void join();
    static void *threadFunc(void*);
    virtual void run()=0;
private:
    pthread_t _th;
    bool isRunning;
};
#endif
