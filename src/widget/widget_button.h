#ifndef WIDGET_BUTTON_H
#define WIDGET_BUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QGraphicsEffect>

#include "basethread.h"

class Widget_Button : public QPushButton
{
    Q_OBJECT

private:
    QString text;

    float alpha = 0;
    float speed = 0.1;

    bool refreshed = false;

public:
    explicit Widget_Button(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setText(QString _text);
    void setTimer(BaseThread *thread);
    inline void setTimer(QTimer& thread){}
    float getAlpha() { return alpha; }
    QString getText() { return text; }

private slots:
    void timeoutRepaint();
};


class Widget_ButtonShadow : public Widget_Button
{
    Q_OBJECT

private:

    QGraphicsDropShadowEffect *effect;

public:
    explicit Widget_ButtonShadow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

};
#endif // WIDGET_BUTTON_H
