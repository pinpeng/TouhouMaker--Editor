#ifndef WIDGET_LINEEDIT_H
#define WIDGET_LINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class EllipticalLineEdit : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *_lebel;

public:
    explicit EllipticalLineEdit(QWidget *parent = nullptr);
    explicit EllipticalLineEdit(const QString& text,const QRect& rect,QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setText(QString text);
    QString text();

private slots:
    void textChangedSlot();

signals:
    void textChanged();

};

#endif // WIDGET_LINEEDIT_H
