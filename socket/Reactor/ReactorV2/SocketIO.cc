#include "SocketIO.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

SocketIO::SocketIO(int fd)
: _fd(fd)
{

}

SocketIO::~SocketIO()
{

}
int SocketIO::readn(char *buf, int len)
{
    int left = len;
    char *pstr = buf;
    int ret = 0;

    //read with possible interuption or overload requested num
    while(left > 0)
    {
        //ret: have read num this round
        ret = read(_fd, pstr, left);
        //interupt
        if(-1 == ret && errno == EINTR)
        {
            //read again
            continue;
        }
        else if(-1 == ret)
        {
            perror("read error -1");
            return len - ret;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            //offset chat* this round
            pstr += ret;
            //fresh left num in all
            left -= ret;
        }
    }

    //return have read
    return len - left;
}

int SocketIO::readLine(char *buf, int len)
{
    int left = len - 1;
    char *pstr = buf;
    int ret = 0, total = 0;

    while(left > 0)
    {
        //read() will move data, not copy data, ban
        //MSG_PEEK不会将缓冲区中的数据进行清空,只会进行拷贝操作
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("readLine error -1");
            return len - ret;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            //line offset footmark
            for(int idx = 0; idx < ret; ++idx)
            {
                if(pstr[idx] == '\n')
                {
                    //footmark to sizeNum
                    int sz = idx + 1;
                    //read a line
                    readn(pstr, sz);
                    //offset Arr head
                    pstr += sz;
                    //string end
                    *pstr = '\0';

                    return total + sz;
                }
            }

            //no '\n', read them all
            readn(pstr, ret);//从内核态拷贝到用户态
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }
    //no '\n' at all ,add one at the end
     *pstr = '\0';

    return total - left;

}

int SocketIO::writen(const char *buf, int len)
{
    int left = len;
    const char *pstr = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = write(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("writen error -1");
            return len - ret;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }

    return len - left;
}
