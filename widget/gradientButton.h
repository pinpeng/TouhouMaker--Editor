#ifndef GRADIENT_BUTTON_H
#define GRADIENT_BUTTON_H

#include <QPushButton>
#include <QTimer>

#include <QGraphicsEffect>

#include "basethread.h"

class GradientButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GradientButton(QWidget *parent = nullptr);
//    void paintEvent(QPaintEvent *) override;

    void setTimer(BaseThread *thread);

    float getAlpha() { return alpha; }

private slots:
    void timeoutRepaint();

protected:
    float alpha = 0;
    float speed = 0.1;

    bool refreshed = false;
};

#endif // GRADIENT_BUTTON_H
