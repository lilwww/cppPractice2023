/**
 * Project 23短期C++提高
 */


#include "EventLoop.h"

/**
 * EventLoop implementation
 */


/**
 * @param acceptor
 */
void EventLoop::EventLoop(Acceptor & acceptor) {

}

void EventLoop::~EventLoop() {

}

/**
 * @return void
 */
void EventLoop::loop() {
    return;
}

/**
 * @return void
 */
void EventLoop::unloop() {
    return;
}

/**
 * @return void
 */
void EventLoop::waitEpollFd() {
    return;
}

/**
 * @return void
 */
void EventLoop::handleNewConnection() {
    return;
}

/**
 * @param fd
 * @return void
 */
void EventLoop::handleMessage(int fd) {
    return;
}

/**
 * @return int
 */
int EventLoop::createEpollFd() {
    return 0;
}

/**
 * @param fd
 * @return void
 */
void EventLoop::addEpollReadFd(int fd) {
    return;
}

/**
 * @param fd
 * @return void
 */
void EventLoop::delEpollReadFd(int fd) {
    return;
}