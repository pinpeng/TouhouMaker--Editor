#include "widget_textEdit.h"

#include "draw.h"

Widget_TextEdit::Widget_TextEdit(QWidget *parent) : QWidget(parent)
{
    Draw::setTextDefault();
    label = new QTextEdit(this);
    label->setGeometry(rect().left() + 24, rect().top() + 18, rect().width() - 56, rect().height() - 32);
    label->setFont(Draw::font);
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setStyleSheet("QTextEdit{border-width:0;border-style:outset;background-color:transparent;color:rgb(" +
                         QString::number(Color(c_textMain).red()) + "," +
                         QString::number(Color(c_textMain).green()) + "," +
                         QString::number(Color(c_textMain).blue()) + ")}");
    label->show();
    connect(label, SIGNAL(textChanged()), this, SLOT(emit_textChanged()));

    text_background = "";
}

void Widget_TextEdit::paintEvent(QPaintEvent *) {
    label->setGeometry(rect().left() + 24, rect().top() + 18, rect().width() - 56, rect().height() - 36);

    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = 32;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 180);
    Draw::pie(w_r - w_h, w_t + w_h, w_h, 0, 90);

    Draw::pie(w_l + w_h, w_b - w_h, w_h, 180, 270);
    Draw::pie(w_r - w_h, w_b - w_h, w_h, 270, 360);

    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

    Draw::rect(w_l, w_t + w_h, w_l + w_h + 1, w_b - w_h);
    Draw::rect(w_r - w_h, w_t + w_h, w_r + 1, w_b - w_h);

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);

    Draw::fillet(w_l + w_h, w_t + w_h, w_h, 90, 180, 2);
    Draw::fillet(w_r - w_h, w_t + w_h, w_h, 0, 90, 2);

    Draw::fillet(w_l + w_h, w_b - w_h, w_h, 180, 270, 2);
    Draw::fillet(w_r - w_h, w_b - w_h, w_h, 270, 360, 2);

    Draw::line(w_l + w_h, w_t, w_r - w_h, w_t, 2);
    Draw::line(w_l + w_h, w_b, w_r - w_h, w_b, 2);

    Draw::line(w_l, w_t + w_h, w_l, w_b - w_h, 2);
    Draw::line(w_r, w_t + w_h, w_r, w_b - w_h, 2);

    if(label->toPlainText().isEmpty()) {
        setPenColor_ca(c_theme, 128);
        Draw::setTextSize(24);
        Draw::text((w_l + w_r) / 2, (w_t + w_b) / 2 + 2, text_background);
    }

    Draw::end();
}

void Widget_TextEdit::setText(QString _text) {
    label->setText(_text);
}

void Widget_TextEdit::setTextSize(float _size)
{
    label->setFont(QFont(Draw::font.family(), _size / Draw::font_scale));
}

QString Widget_TextEdit::text() {
    return label->toPlainText();
}

void Widget_TextEdit::emit_textChanged()
{
    emit textChanged();
}











