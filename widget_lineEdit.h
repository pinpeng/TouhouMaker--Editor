#ifndef WIDGET_LINEEDIT_H
#define WIDGET_LINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class Widget_LineEdit : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *label;

public:
    explicit Widget_LineEdit(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setText(QString _text);
    QString text();

private slots:
    void emit_textChanged();

signals:
    void textChanged();

};

#endif // WIDGET_LINEEDIT_H
