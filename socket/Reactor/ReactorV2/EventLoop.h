/**
 * Project 23短期C++提高
 */

#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H

#include "Acceptor.h"

class EventLoop
{
public:
    /**
     * @param acceptor
     */
    EventLoop(Acceptor &acceptor);

    ~EventLoop();

    void loop();

    void unloop();

private:
    int _epfd;
    bool _isLooping;
    Acceptor &_acceptor;
    vector<struct epoll_event> _evtList;
    void _conns : map<int, shared_ptr<TcpConnection>>;

    void waitEpollFd();

    void handleNewConnection();

    void handleMessage(int fd);

    int createEpollFd();

    void addEpollReadFd(int fd);

    void delEpollReadFd(int fd);
};

#endif //_EVENTLOOP_H