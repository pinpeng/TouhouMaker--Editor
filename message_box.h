#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include "draw.h"

#include <QDialog>
#include <QMessageBox>

class Message_Box : public QDialog
{
    Q_OBJECT
public:
    explicit Message_Box(QString _text, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
#define Message(_str) Message_Box::play(this,_str)
     static void play(QWidget *_this, QString _text);


private:
    QTimer *timer;
    float alpha = 2.0;
    QString text;

private slots:
    void step();

};

#endif // MESSAGE_BOX_H
