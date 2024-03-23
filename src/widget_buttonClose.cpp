#include "widget_buttonClose.h"

#include <QMouseEvent>
#include <complex>
#include "draw.h"


Widget_ButtonClose::Widget_ButtonClose(QWidget *parent) : QPushButton(parent)
{
    setFocusPolicy(Qt::NoFocus);

}

void Widget_ButtonClose::timeoutRepaint()
{
    if(!isActiveWindow()) return;
    if(!underMouse() && (alpha == 0)) return;
    if(underMouse()) { alpha = qMin(alpha + 0.1, 1.0); }
    else { alpha = qMax(alpha - 0.1, 0.0); }
    repaint();
}

void Widget_ButtonClose::paintEvent(QPaintEvent *) {
    float _alpha = -cos(alpha * 3.14159) * 0.5 + 0.5;

    float w_x = rect().left() + 20;
    float w_y = rect().top() + 20;
    float angle1 = ( 45 + _alpha * 180.0) / 180.0 * 3.1416;
    float angle2 = (-45 + _alpha * 180.0) / 180.0 * 3.1416;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_m(c_symbol, c_theme, _alpha);
    Draw::line(w_x + 12 * cos(angle1), w_y - 12 * sin(angle1), w_x - 12 * cos(angle1), w_y + 12 * sin(angle1), 2);
    Draw::line(w_x + 12 * cos(angle2), w_y - 12 * sin(angle2), w_x - 12 * cos(angle2), w_y + 12 * sin(angle2), 2);

    Draw::end();
}


