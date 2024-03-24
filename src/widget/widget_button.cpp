#include "widget/widget_button.h"

#include <QMouseEvent>
#include "draw.h"

#include <QtMath>
#include "globalSource/SourceAgent.h"

Widget_Button::Widget_Button(QWidget *parent) : QPushButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setFixedHeight(80);
    text = "New Button";
    auto& timer = SourceAgent::GetInstance().GetTimer(GlobalSource::TIMER_REPAINT);
    connect(timer.data(), SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
}

void Widget_Button::setText(QString _text) {
    text = _text;
}

void Widget_Button::setTimer(BaseThread *thread)
{

}

void Widget_Button::timeoutRepaint()
{
    if(underMouse()) {
        alpha = qMin(double(alpha + speed), 1.0);
    }
    else {
        alpha = qMax(double(alpha - speed), 0.0);
    }

    if(alpha != 0 && alpha != 1) {
        refreshed = true;
    }

    if(!isActiveWindow()) {
        return;
    }

    if(alpha == 0 || alpha == 1) {
        if(!refreshed) return;
        refreshed = false;
    }
    repaint();
}

void Widget_Button::paintEvent(QPaintEvent *) {

    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_m(c_backgroundMain, c_theme, alpha);
    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
    Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::line(w_l + w_h, w_t, w_r - w_h, w_t, 2);
    Draw::line(w_l + w_h, w_b, w_r - w_h, w_b, 2);
    Draw::fillet(w_l + w_h, w_t + w_h, w_h, 90, 270, 2);
    Draw::fillet(w_r - w_h, w_t + w_h, w_h, 270, 450, 2);

    setPenColor_m(c_theme, c_backgroundMain, alpha);
    Draw::setTextDefault();
    Draw::text(rect().center().x(), rect().center().y() + 4, text, Qt::AlignCenter);
    Draw::end();
}



Widget_ButtonShadow::Widget_ButtonShadow(QWidget *parent) : Widget_Button(parent)
{
    effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(8);
    effect->setColor(QColor(0, 0, 0, 128));
    effect->setOffset(0, 0);
    setGraphicsEffect(effect);
}

void Widget_ButtonShadow::paintEvent(QPaintEvent *)
{
    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;

    float _alpha = getAlpha();
    QString _text = getText();

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_m(c_backgroundMain, c_textMain, _alpha);
    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
    Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

    setPenColor_m(c_textMain, c_backgroundMain, _alpha);
    Draw::setTextDefault();
    Draw::text(rect().center().x(), rect().center().y() + 2, _text, Qt::AlignCenter);
    Draw::end();
}
