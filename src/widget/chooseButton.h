#ifndef WIDGET_CHOOSEBUTTON_H
#define WIDGET_CHOOSEBUTTON_H

#include <QWidget>
#include <QTimer>
#include <QEvent>

#include <QGraphicsEffect>

#include "basethread.h"

class ChooseButton : public QWidget
{
    Q_OBJECT

private:
    QStringList _textList;
    int _index = 0;

    float alpha1 = 0;
    float alpha2 = 0;
    float speed = 0.1;

    bool refreshed = false;

public:
    explicit ChooseButton(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;

    // void setTimer(BaseThread *thread);
    // inline void setTimer(QTimer& timer){}

    void setIndex(int index) { _index = index; };
    int getIndex() { return _index; }

    float getAlpha1() { return alpha1; }
    float getAlpha2() { return alpha2; }

    QString getText(int index) { return _textList[index]; }
    void clear() { _textList.clear(); }
    void addText(QString text) { _textList.append(text); }
    void addTextList(QStringList text) { _textList.append(text); }
    void setText(int index, QString text);

private slots:
    void timeoutRepaint();

signals:
    void indexChanged(int);

};


#endif // WIDGET_CHOOSEBUTTON_H
