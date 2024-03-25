#ifndef WIDGET_BUTTON_H
#define WIDGET_BUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QGraphicsEffect>

class GradientButton : public QPushButton
{
    Q_OBJECT

public:
    explicit GradientButton(QWidget *parent = nullptr);
    explicit GradientButton(const QString& text, const QRect& rect, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

private slots:
    void timeoutRepaint();

private:
    // QString text;

    float _alpha = 0;
    float _speed = 0.1;

    bool _isReflushed = false;
};


// class Widget_ButtonShadow : public GradientButton
// {
//     Q_OBJECT

// private:

//     QGraphicsDropShadowEffect *effect;

// public:
//     explicit Widget_ButtonShadow(QWidget *parent = nullptr);

//     void paintEvent(QPaintEvent *);

// };
#endif // WIDGET_BUTTON_H
