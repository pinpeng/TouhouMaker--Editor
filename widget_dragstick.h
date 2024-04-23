#ifndef WIDGET_DRAGSTICK_H
#define WIDGET_DRAGSTICK_H

#include <QWidget>
#include <QTimer>
#include <QEvent>

#include <QGraphicsEffect>

#include <QtMath>
#include "window_small.h"

class Widget_DragStick : public QWidget
{
    Q_OBJECT

private:
    QString text;
    bool pressed = false;

    float minval;
    float maxval;
    float pos;
    float pos_preview;

    float alpha1 = 0;
    float alpha2 = 0;
    float speed = 0.1;

    bool refreshed = false;

    float showMul = 1.0;

public:
    explicit Widget_DragStick(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    void setText(QString _text) { text = _text; }
    void setTimer(BaseThread *thread);

    void setRange(float _min, float _max) { minval = _min; maxval = _max; }
    float getMin() { return minval; }
    float getMax() { return maxval; }

    void setPos(float _pos) { pos = _pos; };
    int getPos() { return pos; }
    void setValue(float _value) { pos = qMax(0.0f, qMin((_value - minval) / (maxval - minval), 1.0f)); };
    int getValue() { return qMax(minval, qMin(float(floor(minval * (1.0 - pos) + maxval * pos + 0.45)), maxval)); }

    float getAlpha1() { return alpha1; }
    float getAlpha2() { return alpha2; }

    void setShowMul(float _mul) { showMul = _mul; }

private slots:
    void timeoutRepaint();
};


#endif // WIDGET_CHOOSEBUTTON_H
