#include "widget_choosebutton.h"

#include <QMouseEvent>
#include "draw.h"

#include <QtMath>

Widget_ChooseButton::Widget_ChooseButton(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(80);
}

void Widget_ChooseButton::setText(int index, QString _text) {
    text[index] = _text;
}

void Widget_ChooseButton::setTimer(BaseThread *thread)
{
    connect(thread, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
}

void Widget_ChooseButton::timeoutRepaint()
{
    QPoint point = mapFromGlobal(QCursor::pos());
    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;

    if(abs(point.x() - (w_l + w_h)) < w_h - 8 &&
       abs(point.y() - (w_t + w_h)) < w_h - 8) {
        alpha1 = qMin(double(alpha1 + speed), 1.0);
    } else alpha1 = qMax(double(alpha1 - speed), 0.0);

    if(abs(point.x() - (w_r - w_h)) < w_h - 8 &&
       abs(point.y() - (w_t + w_h)) < w_h - 8) {
        alpha2 = qMin(double(alpha2 + speed), 1.0);
    } else alpha2 = qMax(double(alpha2 - speed), 0.0);

    if((alpha1 != 0 && alpha1 != 1) || (alpha2 != 0 && alpha2 != 1)) refreshed = true;

    if(!isActiveWindow()) return;
    if((alpha1 == 0 || alpha1 == 1) && (alpha2 == 0 || alpha2 == 1)) {
        if(!refreshed) return;
        refreshed = false;
    }
    repaint();
}

void Widget_ChooseButton::paintEvent(QPaintEvent *) {

    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
    Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::line(w_l + w_h, w_t, w_r - w_h, w_t, 2);
    Draw::line(w_l + w_h, w_b, w_r - w_h, w_b, 2);
    Draw::fillet(w_l + w_h, w_t + w_h, w_h, 90, 270, 2);
    Draw::fillet(w_r - w_h, w_t + w_h, w_h, 270, 450, 2);

    setPenColor_false();
    setBrushColor_m(c_backgroundMain, c_theme, alpha1);
    Draw::circle(w_l + w_h, w_t + w_h, w_h - 8);

    setPenColor_m(c_theme, c_backgroundMain, alpha1);
    Draw::line(w_l + w_h - 4, w_t + w_h, w_l + w_h + 4, w_t + w_h - 8, 4);
    Draw::line(w_l + w_h - 4, w_t + w_h, w_l + w_h + 4, w_t + w_h + 8, 4);

    setPenColor_false();
    setBrushColor_m(c_backgroundMain, c_theme, alpha2);
    Draw::circle(w_r - w_h, w_t + w_h, w_h - 8);

    setPenColor_m(c_theme, c_backgroundMain, alpha2);
    Draw::line(w_r - w_h + 4, w_t + w_h, w_r - w_h - 4, w_t + w_h - 8, 4);
    Draw::line(w_r - w_h + 4, w_t + w_h, w_r - w_h - 4, w_t + w_h + 8, 4);

    setPenColor_c(c_theme);
    Draw::setTextDefault();

    if(text.size()) {
        if(index < 0) index = 0;
        if(index > text.size()) index = text.size() - 1;
        setPenColor_c(c_theme);
        Draw::text(rect().center().x(), rect().center().y() + 2, text[index], Qt::AlignCenter);
    }
    Draw::end();
}

void Widget_ChooseButton::mousePressEvent(QMouseEvent *event)
{
    if(!text.size()) return;

    if(event->button() == Qt::LeftButton) {
        float w_l = rect().x() + 12;
        float w_r = rect().right() - 8;
        float w_t = rect().y() + 8;
        float w_b = rect().bottom() - 8;
        float w_h = (w_b - w_t) / 2;

        int tmp = index;
        if(abs(event->y() - (w_t + w_h)) < w_h - 8) {
            if(abs(event->x() - (w_l + w_h)) < w_h - 8) {
                index = index - 1;
                if(index < 0) index = text.size() - 1;
            } else if(abs(event->x() - (w_r - w_h)) < w_h - 8) {
                index = index + 1;
                if(index >= text.size()) index = 0;
            }
        }
        if(tmp != index) emit indexChanged(index);
    }
    repaint();
}



