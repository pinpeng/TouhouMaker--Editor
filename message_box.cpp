#include "message_box.h"

#include <qt_windows.h>

Message_Box::Message_Box(QString _text, QWidget *parent) : QDialog(parent)
{
    setWindowModified(false);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);

    timer = new QTimer(this);
    timer->start(1000 / 60);

    text = _text;

    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
}

void Message_Box::paintEvent(QPaintEvent *)
{
    QPoint mid = rect().center();
    Draw::begin(this);
    Draw::setAntialising();
    Draw::setPenColor(false);
    Draw::setBrushColor(0, 0, 0, 128);
    Draw::pie(mid.x() - 96, mid.y(), 40, 90, 270);
    Draw::pie(mid.x() + 96, mid.y(), 40, 270, 450);
    Draw::rect(mid.x() - 96, mid.y() - 40, mid.x() + 96, mid.y() + 40);
    Draw::setPenColor(255, 255, 255);
    Draw::setTextDefault();
    Draw::text(mid.x(), mid.y() + 2, text);
    Draw::end();
}

void Message_Box::play(QWidget *_this, QString _text)
{
    Message_Box *tmp = new Message_Box(_text);
    tmp->show();
    FlashWindow(HWND(_this->winId()), false);
}

void Message_Box::step()
{
    alpha -= 0.02;
    setWindowOpacity(alpha > 1.0? 1.0: alpha);
    if(alpha <= 0) close();
}
