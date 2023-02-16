#include "Thread.h"
#include <stdio.h>
Thread::Thread():
_th(0)
,isRunning(false)
{

}
Thread::~Thread(){
    if(isRunning){
        int ret=pthread_detach(_th);
        if(ret){
            perror("pthread_detach\n");
            return;
         }
        isRunning=false;
    }
    
}
void Thread::start()
{
    int ret=pthread_create(&_th,nullptr,threadFunc,this);
    if(ret){
        perror("pthread_create\n");
        return;
    }
    isRunning=true;
}

void Thread::join()
{
    if(isRunning){
        int ret = pthread_join(_th,nullptr);
        if(ret){
            perror("pthread_join\n");
            return;
        }
        isRunning=false;
    }
}
void* Thread::threadFunc(void* arg){
    Thread* tmp=static_cast<Thread*> (arg);
    if(tmp){
        tmp->run();
    }
    pthread_exit(nullptr);
}
