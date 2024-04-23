#ifndef WIDGET_CHOOSEBUTTON_H
#define WIDGET_CHOOSEBUTTON_H

#include <QWidget>
#include <QTimer>
#include <QEvent>

#include <QGraphicsEffect>

#include "window_small.h"

class Widget_ChooseButton : public QWidget
{
    Q_OBJECT

private:
    QStringList text;
    int index = 0;

    float alpha1 = 0;
    float alpha2 = 0;
    float speed = 0.1;

    bool refreshed = false;

public:
    explicit Widget_ChooseButton(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;

    void setTimer(BaseThread *thread);

    void setIndex(int _index) { index = _index; };
    int getIndex() { return index; }

    float getAlpha1() { return alpha1; }
    float getAlpha2() { return alpha2; }

    QString getText(int index) { return text[index]; }
    void clear() { text.clear(); }
    void addText(QString _text) { text.append(_text); }
    void addTextList(QStringList _text) { text.append(_text); }
    void setText(int index, QString _text);

private slots:
    void timeoutRepaint();

signals:
    void indexChanged(int);

};


#endif // WIDGET_CHOOSEBUTTON_H
