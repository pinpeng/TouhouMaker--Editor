#include "widget/closeButton.h"

#include <QMouseEvent>
#include <complex>
#include "draw.h"
#include "globalSource/sourceAgent.h"

CloseButton::CloseButton(QWidget *parent): 
    QPushButton(parent),_alpha(0)
{
    auto& repaintTimer = SourceAgent::GetInstance().GetTimer(GlobalSource::TIMER_REPAINT);
    connect(repaintTimer.data(), SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
    setFocusPolicy(Qt::NoFocus);
}

void CloseButton::timeoutRepaint()
{
    if(!isActiveWindow()) return;

    if(!underMouse() && (_alpha == 0)) return;
    
    if(underMouse()){
        _alpha = qMin(_alpha + 0.1, 1.0); 
    }
    else {
        _alpha = qMax(_alpha - 0.1, 0.0); 
    }

    repaint();
}

void CloseButton::paintEvent(QPaintEvent *) {
    float alpha = -cos(_alpha * 3.14159) * 0.5 + 0.5;

    float w_x = rect().left() + 20;
    float w_y = rect().top() + 20;
    float angle1 = ( 45 + alpha * 180.0) / 180.0 * 3.1416;
    float angle2 = (-45 + alpha * 180.0) / 180.0 * 3.1416;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_m(c_symbol, c_theme, alpha);
    Draw::line(w_x + 12 * cos(angle1), w_y - 12 * sin(angle1), w_x - 12 * cos(angle1), w_y + 12 * sin(angle1), 2);
    Draw::line(w_x + 12 * cos(angle2), w_y - 12 * sin(angle2), w_x - 12 * cos(angle2), w_y + 12 * sin(angle2), 2);

    Draw::end();
}


