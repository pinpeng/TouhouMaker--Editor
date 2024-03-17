#ifndef WIDGET_BUTTONCLOSE_H
#define WIDGET_BUTTONCLOSE_H

#include <QPushButton>
#include <QTimer>

class Widget_ButtonClose : public QPushButton
{
    Q_OBJECT

private:
    //QTimer *timer;
    float alpha = 0;

public:
    explicit Widget_ButtonClose(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

public slots:
    void timeoutRepaint();
};

#endif // WIDGET_BUTTONCLOSE_H
