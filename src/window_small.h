#ifndef WINDOW_SMALL_H
#define WINDOW_SMALL_H

#include <QWidget>
#include <QTimer>

#include <QMouseEvent>
#include <QPaintEvent>

#include "widget_buttonClose.h"
#include "message_box.h"

#include "draw.h"

#include <QThread>
#include <QLabel>

class BaseThread : public QThread
{
    Q_OBJECT

public:
    BaseThread();
    ~BaseThread();

protected:
    void run();

private:
    QTimer *timer;

public slots:
    void timeoutRequest();

signals:
    void timeout();

};

class Window_small : public QWidget
{
    Q_OBJECT

public:
    explicit Window_small(QWidget *parent = nullptr);
    ~Window_small();

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


#endif // WINDOW_SMALL_H
