#ifndef SMALL_WINDOW_H
#define SMALL_WINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

#include "widget_buttonClose.h"
#include "message_box.h"

#include "draw.h"
#include "basethread.h"

class SmallWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWindow(QWidget *parent = nullptr);
    ~SmallWindow();

    virtual void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    void mousePress(QMouseEvent *event);
    bool mousePressFunc(QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mouseRelease();

    BaseThread *timer;

    bool isClosing = false;
private:

    bool isMoving = false;
    QPoint startMovingPos;

    float baseAlpha = 0.0;


    Widget_ButtonClose *buttonClose;

public slots:

    virtual void end();
    void baseAlphaChange();

signals:
    void closed();

};


#endif // SMALL_WINDOW_H
