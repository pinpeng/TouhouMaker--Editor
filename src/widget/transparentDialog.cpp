#include "TransparentDialog.h"

// #include <qt_windows.h>

// TransparentDialog::TransparentDialog(QString _text, QWidget *parent) : QDialog(parent)
// {
//     setWindowModified(false);
//     setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
//     setAttribute(Qt::WA_DeleteOnClose);
//     setAttribute(Qt::WA_TranslucentBackground);

//     timer = new QTimer(this);
//     timer->start(1000 / 60);

//     _text = _text;

//     connect(timer, SIGNAL(timeout()), this, SLOT(step()));
// }

TransparentDialog::TransparentDialog(QWidget *parent) : QDialog(parent)
{
    setWindowModified(false);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);

    timer = new QTimer(this);
    timer->start(1000 / 60);

    // _text = _text;

    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
}

void TransparentDialog::paintEvent(QPaintEvent *)
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
    Draw::text(mid.x(), mid.y() + 2, _text);
    Draw::end();
}

void TransparentDialog::play(QWidget *_this, QString text)
{
    static TransparentDialog tmp;
    tmp._alpha = 2.0;
    tmp._text = text;
    tmp.show();
    // FlashWindow(HWND(_this->winId()), false);
}

void TransparentDialog::play(const QString& text){
    static TransparentDialog tmp;
    tmp._alpha = 2.0;
    tmp._text = text;
    tmp.show();
}

void TransparentDialog::step()
{
    _alpha -= 0.02;
    setWindowOpacity(_alpha > 1.0? 1.0: _alpha);
    if(_alpha <= 0){
        hide();
    }
}
