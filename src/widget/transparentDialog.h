#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include "draw.h"

#include <QDialog>
#include <QMessageBox>

/**
 * @brief 提示框，使用时要用play单例
*/
class TransparentDialog : public QDialog
{
    Q_OBJECT
public:
    // explicit TransparentDialog(QString _text, QWidget *parent = nullptr);
    explicit TransparentDialog(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
// #define TransparentDialog::play(_str) TransparentDialog::play(this,_str)
    static void play(QWidget *_this, QString _text);
    static void play(const QString& text);


private:
    QTimer *timer;
    float _alpha = 2.0;
    QString _text;

private slots:
    void step();

};

#endif // MESSAGE_BOX_H
