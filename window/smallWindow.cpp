#include "window/smallWindow.h"

void SmallWindow::paintEvent(QPaintEvent *) {
    Draw::smallWindow(this, this);
}

SmallWindow::SmallWindow(QWidget *parent) : QWidget(parent)
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

SmallWindow::~SmallWindow()
{
    timer->quit();
    timer->wait();
    delete timer;
}

void SmallWindow::mousePressEvent(QMouseEvent *event) {
    mousePress(event);
}

void SmallWindow::mouseMoveEvent(QMouseEvent *event) {
    mouseMove(event);
}

void SmallWindow::mouseReleaseEvent(QMouseEvent *) {
    mouseRelease();
}

void SmallWindow::mousePress(QMouseEvent *event)
{
    if(mousePressFunc(event)) return;
}

bool SmallWindow::mousePressFunc(QMouseEvent *event)
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

void SmallWindow::mouseMove(QMouseEvent *event)
{
    if(isMoving) { move(pos() + event->pos() - startMovingPos); }
}

void SmallWindow::mouseRelease()
{
    isMoving = false;
}

void SmallWindow::end()
{
    isClosing = true;
    emit closed();
}

void SmallWindow::baseAlphaChange()
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
