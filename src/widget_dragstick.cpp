#include "widget_dragstick.h"

#include <QMouseEvent>
#include "draw.h"


Widget_DragStick::Widget_DragStick(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setFixedHeight(80);
    text = "%";
    minval = 0.0f;
    maxval = 100.0f;
    pos = 0.5f;
    pos_preview = pos;
}

void Widget_DragStick::setTimer(BaseThread *thread)
{
    connect(thread, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
}

void Widget_DragStick::timeoutRepaint()
{
    QPoint point = mapFromGlobal(QCursor::pos());
    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;
    float r = 8;

    pos_preview = pos_preview * 0.8 + pos * 0.2;

    if(abs(point.y() - (w_t + w_h + r * 2)) < w_h &&
       w_l < point.x() && point.x() < w_r) {
        alpha1 = qMin(double(alpha1 + speed), 1.0);
    } else alpha1 = qMax(double(alpha1 - speed), 0.0);

    if(alpha1 == 0) pressed = false;

    if(pressed) {
        alpha2 = qMin(double(alpha2 + speed), 1.0);
    } else alpha2 = qMax(double(alpha2 - speed), 0.0);

    if((alpha1 != 0 && alpha1 != 1) || (alpha2 != 0) || abs(pos_preview - pos) < 0.5) refreshed = true;

    if(!isActiveWindow()) return;
    if((alpha1 == 0 || alpha1 == 1) && (alpha2 == 0)) {
        if(!refreshed) return;
        refreshed = false;
    }
    repaint();
}

void Widget_DragStick::paintEvent(QPaintEvent *) {

    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;
    float r = 8;
    float w_w = w_r - w_l - w_h * 2;


    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_c(c_symbol);
    Draw::circle(w_l + w_h, w_t + w_h + r * 2, r);
    Draw::circle(w_r - w_h, w_t + w_h + r * 2, r);
    Draw::rect(w_l + w_h, w_t + w_h + r * 2 - r, w_r - w_h, w_t + w_h + r * 2 + r);

    setBrushColor_c(c_theme);
    Draw::circle(w_l + w_h, w_t + w_h + r * 2, r);
    Draw::rect(w_l + w_h, w_t + w_h + r * 2 - r, w_l + w_h + w_w * pos_preview, w_t + w_h + r * 2 + r);
    Draw::circle(w_l + w_h + w_w * pos_preview, w_t + w_h + r * 2, r * (1.0 + alpha1));

    if(alpha2 > 0) {
        setBrushColor_c(c_backgroundMain);
        Draw::circle(w_l + w_h + w_w * pos_preview, w_t + w_h + r * 2, r * (alpha1 / 2 + alpha2));
    }

    setPenColor_c(c_theme);
    Draw::setTextDefault();
    Draw::setTextSize(14);
    float _tmp_alpha;

    _tmp_alpha = 0;
    if(w_w * pos_preview < 16) _tmp_alpha = qMax(0.0f, qMin((1 - w_w * pos_preview / 16) * alpha1 * 1.0f, 1.0f));
    Draw::text(w_l + w_h - 12, w_t + w_h + r * (1 - _tmp_alpha),
               QString::number(floor(minval * showMul + 0.45)), Qt::AlignHCenter | Qt::AlignBottom);
    _tmp_alpha = 0;
    if(w_w * pos_preview > w_w - 16) _tmp_alpha = qMax(0.0f, qMin((1 - w_w * (1 - pos_preview) / 16) * alpha1 * 1.0f, 1.0f));
    Draw::text(w_r - w_h + 12, w_t + w_h + r * (1 - _tmp_alpha),
               QString::number(floor(maxval * showMul + 0.45)), Qt::AlignHCenter | Qt::AlignBottom);

    _tmp_alpha = 255.0;
    if(w_w * pos_preview < 16) _tmp_alpha = qMax(0.0f, qMin((w_w * pos / 8 - 1) * 255.0f, 255.0f));
    if(w_w * pos_preview > w_w - 16) _tmp_alpha = qMax(0.0f, qMin((w_w * (1 - pos_preview) / 8 - 1) * 255.0f, 255.0f));
    setPenColor_ca(c_theme, _tmp_alpha);
    Draw::setTextSize(10);
    Draw::text(w_l + w_h + w_w * pos_preview, w_t + w_h + r * (1.0 - alpha1), QString::number(
                   floor((minval * (1.0 - pos_preview) + maxval * pos_preview) * showMul + 0.45) ) + text, Qt::AlignHCenter | Qt::AlignBottom);

    Draw::end();

}

void Widget_DragStick::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        pressed = true;
    }
}

void Widget_DragStick::mouseMoveEvent(QMouseEvent *event)
{
    if(pressed) {

        float w_l = rect().x() + 12;
        float w_r = rect().right() - 8;
        float w_t = rect().y() + 8;
        float w_b = rect().bottom() - 8;
        float w_h = (w_b - w_t) / 2;
        float w_w = w_r - w_l - w_h * 2;

        float tmp = qMax(0.0f, qMin((event->x() - (w_l + w_h)) / w_w, 1.0f));
        for(float i = 0; i <= 1.0; i += 0.10) {
            if(abs(tmp - i) < 0.02) tmp = i;
        }
        setPos(tmp);
    }
}

void Widget_DragStick::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}



