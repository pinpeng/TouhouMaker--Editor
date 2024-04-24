#include "window_small.h"

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


void Window_small::paintEvent(QPaintEvent *) {
    Draw::smallWindow(this, this);
}

Window_small::Window_small(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/logo/mscb_icon.ico"));
    setMinimumSize(200, 180);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.0);

    timer = new BaseThread;
    connect(timer, SIGNAL(timeout()), this, SLOT(baseAlphaChange()));
    timer->start();

    buttonClose = new Widget_ButtonClose(this);
    connect(buttonClose, SIGNAL(pressed()), this, SLOT(end()));
    connect(timer, SIGNAL(timeout()), buttonClose, SLOT(timeoutRepaint()));
}

Window_small::~Window_small()
{
    timer->quit();
    timer->wait();
    delete timer;
}

void Window_small::mousePressEvent(QMouseEvent *event) {
    mousePress(event);
}

void Window_small::mouseMoveEvent(QMouseEvent *event) {
    mouseMove(event);
}

void Window_small::mouseReleaseEvent(QMouseEvent *) {
    mouseRelease();
}

void Window_small::mousePress(QMouseEvent *event)
{
    if(mousePressFunc(event)) return;
}

bool Window_small::mousePressFunc(QMouseEvent *event)
{
    if(isClosing) return true;
    if(event->button() == Qt::LeftButton) {
        if(event->pos().y() > rect().y() + 8 && event->pos().y() < rect().y() + 56) {
            isMoving = true;
            startMovingPos = event->pos();
        }
    }
    return false;
}

void Window_small::mouseMove(QMouseEvent *event)
{
    if(isMoving) { move(pos() + event->pos() - startMovingPos); }
}

void Window_small::mouseRelease()
{
    isMoving = false;
}

void Window_small::end()
{
    isClosing = true;
    emit closed();
}

void Window_small::baseAlphaChange()
{
    if(!isActiveWindow()) {
        return;
    }
    if(!isClosing) {
        if(baseAlpha < 1.0) {
            baseAlpha = qMin(baseAlpha + 0.1, 1.0);
            setWindowOpacity(baseAlpha);
        }
    } else {
        if(baseAlpha > 0.0) {
            baseAlpha = qMax(baseAlpha - 0.1, 0.0);
            setWindowOpacity(baseAlpha);
        } else close();
    }

    buttonClose->setGeometry(rect().right() - 60, rect().top() + 12, 40, 40);
}
