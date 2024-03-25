#include "widget/gradientButton.h"

#include <QMouseEvent>
#include "draw.h"

#include <QtMath>
#include "globalSource/SourceAgent.h"

GradientButton::GradientButton(QWidget *parent) : QPushButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setFixedHeight(80);
    auto& timer = SourceAgent::GetInstance().GetTimer(GlobalSource::TIMER_REPAINT);
    connect(timer.data(), SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
}

GradientButton::GradientButton(const QString& text, const QRect& rect, QWidget *parent) : GradientButton(parent)
{
    setText(text);
    setGeometry(rect);
}

void GradientButton::timeoutRepaint()
{
    if(underMouse()) {
        _alpha = qMin(double(_alpha + _speed), 1.0);
    }
    else {
        _alpha = qMax(double(_alpha - _speed), 0.0);
    }

    if(_alpha != 0 && _alpha != 1) {
        _isReflushed = true;
    }

    if(!isActiveWindow()) {
        return;
    }

    if(_alpha == 0 || _alpha == 1) {
        if(!_isReflushed) return;
        _isReflushed = false;
    }
    repaint();
}

void GradientButton::paintEvent(QPaintEvent *) {

    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_m(c_backgroundMain, c_theme, _alpha);
    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
    Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::line(w_l + w_h, w_t, w_r - w_h, w_t, 2);
    Draw::line(w_l + w_h, w_b, w_r - w_h, w_b, 2);
    Draw::fillet(w_l + w_h, w_t + w_h, w_h, 90, 270, 2);
    Draw::fillet(w_r - w_h, w_t + w_h, w_h, 270, 450, 2);

    setPenColor_m(c_theme, c_backgroundMain, _alpha);
    Draw::setTextDefault();
    Draw::text(rect().center().x(), rect().center().y() + 4, text(), Qt::AlignCenter);
    Draw::end();
}

// Widget_ButtonShadow::Widget_ButtonShadow(QWidget *parent) : GradientButton(parent)
// {
//     effect = new QGraphicsDropShadowEffect();
//     effect->setBlurRadius(8);
//     effect->setColor(QColor(0, 0, 0, 128));
//     effect->setOffset(0, 0);
//     setGraphicsEffect(effect);
// }

// void Widget_ButtonShadow::paintEvent(QPaintEvent *)
// {
//     float w_l = rect().x() + 12;
//     float w_r = rect().right() - 8;
//     float w_t = rect().y() + 8;
//     float w_b = rect().bottom() - 8;
//     float w_h = (w_b - w_t) / 2;

//     float _alpha = getAlpha();
//     QString _text = getText();

//     Draw::begin(this);
//     Draw::setAntialising(true);

//     setPenColor_false();
//     setBrushColor_m(c_backgroundMain, c_textMain, _alpha);
//     Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
//     Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
//     Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

//     setPenColor_m(c_textMain, c_backgroundMain, _alpha);
//     Draw::setTextDefault();
//     Draw::text(rect().center().x(), rect().center().y() + 2, _text, Qt::AlignCenter);
//     Draw::end();
// }
