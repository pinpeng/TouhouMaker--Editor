#include "basethread.h"

BaseThread::BaseThread()
{

}

BaseThread::~BaseThread()
{

}

void BaseThread::run()
{
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeoutRequest()));
    connect(this, SIGNAL(finished()), _timer, SLOT(stop()));
    _timer->start(1000 / 60);
    exec();
}

void BaseThread::timeoutRequest()
{
    emit timeout();
}
