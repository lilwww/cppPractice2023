#include "TaskQueue.h"
#include "MutexLock.h"
TaskQueue::TaskQueue(size_t s):
queSize(s)
,taskQ()
,notExit(true)
,_mutex()
,notEmpty(_mutex)
,notFull(_mutex)
{

}

TaskQueue::~TaskQueue(){

}

bool TaskQueue::isEmpty() const{
    return taskQ.empty();
}
bool TaskQueue::isFull() const{
    return taskQ.size()== queSize;
}

ElemTy TaskQueue::pop(){
    MutexLockGuard autoLock(_mutex);
    while(isEmpty()&&notExit){
        notEmpty.wait();
    }
    ElemTy tmp=taskQ.front();
    taskQ.pop();
    notFull.notify();
    return tmp;
}
void TaskQueue::push(ElemTy e){
    MutexLockGuard autoLock(_mutex);

    while(isFull()){
        notFull.wait();
    }

    notEmpty.notify();
}
void TaskQueue::wakeup(){
    notExit=false;
    notEmpty.notifyAll();
}
