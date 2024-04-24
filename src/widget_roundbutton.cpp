#include "widget_roundbutton.h"

#include "draw.h"

Widget_RoundButton::Widget_RoundButton(QWidget *parent) : QRadioButton(parent)
{
    setFixedHeight(36);
}

void Widget_RoundButton::timeoutRepaint()
{
    if(underMouse()) alpha = qMin(double(alpha + speed), 1.0);
    else alpha = qMax(double(alpha - speed), 0.0);

    checkedAlpha = isChecked()? qMin(checkedAlpha + 0.1, 1.0): qMax(checkedAlpha - 0.1, 0.0);

    if((alpha != 0 && alpha != 1) || (checkedAlpha != 0 && checkedAlpha != 1)) refreshed = true;

    if(!isActiveWindow()) return;
    if((alpha == 0 || alpha == 1) && (checkedAlpha == 0 || checkedAlpha == 1)) {
        if(!refreshed) return;
        refreshed = false;
    }
    repaint();
}

void Widget_RoundButton::paintEvent(QPaintEvent *)
{

    Draw::begin(this);
    Draw::setAntialising(true);
    setPenColor_m(c_itemEdge, c_theme, alpha);
    setBrushColor_c(c_backgroundMain);
    Draw::circle(rect().x() + 16, rect().y() + 20, 14, 2.0);

    if(checkedAlpha != 0.0) {
        float tmp;
        setPenColor_false();
        setBrushColor_c(c_theme);
        tmp = qMin(16.0, 24.0 * checkedAlpha);
        Draw::circle(rect().x() + 16, rect().y() + 20, tmp);
        setBrushColor_c(c_backgroundMain);
        tmp = qMax(0.0, 16.0 * (checkedAlpha - 0.5));
        Draw::circle(rect().x() + 16, rect().y() + 20, tmp);
    }
    setPenColor_m(c_textMain, c_theme, alpha);
    Draw::setTextDefault();
    Draw::setTextSize(18);
    Draw::text(rect().left() + 36, rect().center().y() + 4, text(), Qt::AlignLeft | Qt::AlignVCenter);

    Draw::end();
}

void Widget_RoundButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        float x = event->x();
        float y = event->y();
        if(rect().x() < x && x < rect().right() - 16 && rect().y() < y && y < rect().y() + 36) {
            if(!isChecked()) {
                setChecked(true);
                emit stateChanged();
            }
        }
    }
}

void Widget_RoundButton::keyPressEvent(QKeyEvent *event)
{

}

void Widget_RoundButton::slow()
{
    speed = 0.05;
}

void Widget_RoundButton::setTimer(BaseThread *thread)
{
    connect(thread, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
}
