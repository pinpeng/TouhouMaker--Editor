#ifndef BASETHREAD_H
#define BASETHREAD_H

#include <QThread>
#include <QTimer>

class BaseThread : public QThread
{
    Q_OBJECT

public:
    BaseThread();
    ~BaseThread();

protected:
    void run();

private:
    QTimer *_timer;

public slots:
    void timeoutRequest();

signals:
    void timeout();

};
#endif // BASETHREAD_H
