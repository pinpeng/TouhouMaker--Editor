
#ifndef WIDGET_TEXTEDIT_H
#define WIDGET_TEXTEDIT_H

#include <QTextEdit>
#include <QWidget>

class Widget_TextEdit : public QWidget
{
    Q_OBJECT

private:
    QTextEdit *label;

public:
    explicit Widget_TextEdit(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setText(QString _text);
    void setFont(QFont _font) { label->setFont(_font); };
    void setTextSize(float _size);
    QString text();

    void setBackgroundText(QString _text) { text_background = _text; };

private:

    QString text_background;

private slots:
    void emit_textChanged();


signals:
    void textChanged();

};

#endif // WIDGET_TEXTEDIT_H

