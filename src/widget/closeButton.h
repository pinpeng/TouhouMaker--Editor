#ifndef WIDGET_BUTTONCLOSE_H
#define WIDGET_BUTTONCLOSE_H

#include <QPushButton>
#include <QTimer>

/**
 * @brief 关闭按钮，重写了绘制函数，会在鼠标悬浮时使X旋转
*/
class CloseButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CloseButton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;

public slots:
    void timeoutRepaint();

private:
    float _alpha;
};

#endif // WIDGET_BUTTONCLOSE_H
