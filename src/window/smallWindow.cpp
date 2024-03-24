#include "window/smallWindow.h"
#include "globalSource/sourceAgent.h"

void SmallWindow::paintEvent(QPaintEvent *) {
    Draw::smallWindow(this, this);
}

SmallWindow::SmallWindow(QWidget *parent) : QWidget(parent)
{
    // QTimer& timer = SourceAgent::GetInstance().ge
    setWindowIcon(QIcon(":/logo/mscb_icon.ico"));
    setMinimumSize(200, 180);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.0);

    // timer = new BaseThread;
    _closeButton = new CloseButton(this);
    connect(_closeButton, SIGNAL(pressed()), this, SLOT(end()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(baseAlphaChange()));
    _timer.start(1000/60);
}

SmallWindow::~SmallWindow()
{
    // timer->quit();
    // timer->wait();
    // delete timer;
}

void SmallWindow::mousePressEvent(QMouseEvent *event) {
    if(_isClosing) return;
    if(event->button() == Qt::LeftButton) {
        if(event->pos().y() > rect().y() + 8 && event->pos().y() < rect().y() + 56) {
            _isMoving = true;
            startMovingPos = event->pos();
        }
    }
}

void SmallWindow::mouseMoveEvent(QMouseEvent *event) {
    if(_isMoving) { move(pos() + event->pos() - startMovingPos); }
}

void SmallWindow::mouseReleaseEvent(QMouseEvent *) {
    _isMoving = false;
}

void SmallWindow::end()
{
    _isClosing = true;
    emit closed();
}

void SmallWindow::baseAlphaChange()
{
    // 如果不是当前窗口，直接返回
    if(!isActiveWindow()) {
        return;
    }
    // 如果不是正在关闭，则透明度提升
    if(!_isClosing) {
        if(_windowOpacity < 1.0) {
            _windowOpacity = qMin(_windowOpacity + 0.1, 1.0);
            setWindowOpacity(_windowOpacity);
        }
    }
    // 如果正在关闭 
    else {
        // 透明度没降为0,则降透明度
        if(_windowOpacity > 0.0) {
            _windowOpacity = qMax(_windowOpacity - 0.1, 0.0);
            setWindowOpacity(_windowOpacity);
        }
        // 透明度降为0,则关闭窗口 
        else if(_windowOpacity <= 0.0){
            close();
        }
    }

    _closeButton->setGeometry(rect().right() - 60, rect().top() + 12, 40, 40);
}
