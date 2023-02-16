#include "ThreadPool.h"
#include "WorkThread.h"
#include <unistd.h>
ThreadPool::ThreadPool(size_t tNum,size_t qNum):
_thNum(tNum)
,_tqSize(qNum)
,_isExit(false)
,_taskQ(qNum)
{
    _threads.reserve(tNum);
}
ThreadPool::~ThreadPool(){
    if(!_isExit){
        stop();
    }
}
void ThreadPool::start(){
    for(size_t idx=0;idx!=_thNum;idx++){
        std::unique_ptr<Thread> tmp(new WorkThread(*this));
        _threads.push_back(std::move(tmp));
    }
    int i=1;
    for(auto&t:_threads){
        t->start();
    }
}
void ThreadPool::stop(){
    while(!_taskQ.isEmpty()){
        sleep(1);
    }
    _isExit=true;
   _taskQ.wakeup();
   
   for(auto&t:_threads){
       t->join();
    }
    
}
void ThreadPool::addTask(ElemTy e){
    if(e){
        _taskQ.push(e);
    }
}
ElemTy ThreadPool::getTask(){
    return _taskQ.pop();
}
void ThreadPool::threadFunc(){
   
    while(!_isExit){
        ElemTy t=getTask();
        
        if(t){
            t->process();   
        }
    }
}
