#include "basethread.h"

BaseThread::BaseThread()
{

}

BaseThread::~BaseThread()
{

}

void BaseThread::run()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutRequest()));
    connect(this, SIGNAL(finished()), timer, SLOT(stop()));
    timer->start(1000 / 60);
    exec();
}

void BaseThread::timeoutRequest()
{
    emit timeout();
}
