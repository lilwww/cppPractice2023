#ifndef _TASK_H_
#define _TASK_H_
#include <time.h>
#include <stdlib.h>
#include <iostream>
class Task
{
public:
    Task() {}
    ~Task() {}
    virtual
        void process()=0;
private:

};
#endif
