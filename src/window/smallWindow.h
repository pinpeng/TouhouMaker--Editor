#ifndef SMALL_WINDOW_H
#define SMALL_WINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QTimer>

#include "widget/closeButton.h"
#include "message_box.h"
#include "draw.h"
// #include "basethread.h"

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

protected:
    QTimer _timer;
    bool _isClosing = false;
    
private:
    bool _isMoving = false;
    QPoint startMovingPos;

    float _windowOpacity = 0.0;


    CloseButton* _closeButton;

public slots:

    virtual void end();
    void baseAlphaChange();

signals:
    void closed();

};


#endif // SMALL_WINDOW_H
