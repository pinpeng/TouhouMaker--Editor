#ifndef WIDGET_ROUNDBUTTON_H
#define WIDGET_ROUNDBUTTON_H

#include <QRadioButton>
#include <QButtonGroup>

#include <QTimer>

#include <QMouseEvent>
#include "basethread.h"

class Widget_RoundButton : public QRadioButton
{
    Q_OBJECT

private:
    //QTimer *timer;

    float alpha = 0;
    float checkedAlpha = 0;
    float speed = 0.1;

    bool refreshed = false;

public:
    explicit Widget_RoundButton(QWidget *parent = nullptr);

     void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void slow();

private slots:
    void timeoutRepaint();

signals:
    void stateChanged();
};

#endif // WIDGET_ROUNDBUTTON_H
