#include "widget/widget_lineEdit.h"

#include "draw.h"

Widget_LineEdit::Widget_LineEdit(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(80);
    Draw::setTextDefault();
    label = new QLineEdit(this);
    label->setGeometry(rect().left() + 24, rect().top(), rect().width() - 48, rect().height());
    label->setFont(Draw::font);
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent;color:rgb(" +
                         QString::number(Color(c_textMain).red()) + "," +
                         QString::number(Color(c_textMain).green()) + "," +
                         QString::number(Color(c_textMain).blue()) + ")}");
    label->show();

    connect(label, SIGNAL(textChanged(QString)), this, SLOT(emit_textChanged()));
}

void Widget_LineEdit::paintEvent(QPaintEvent *) {
    label->setGeometry(rect().left() + 24, rect().top(), rect().width() - 48, rect().height());

    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;
    float w_h = (w_b - w_t) / 2;

    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
    Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::line(w_l + w_h, w_t, w_r - w_h, w_t, 2);
    Draw::line(w_l + w_h, w_b, w_r - w_h, w_b, 2);
    Draw::fillet(w_l + w_h, w_t + w_h, w_h, 90, 270, 2);
    Draw::fillet(w_r - w_h, w_t + w_h, w_h, 270, 450, 2);

    Draw::end();
}

void Widget_LineEdit::setText(QString _text) {
    label->setText(_text);
}

QString Widget_LineEdit::text() {
    return label->text();
}

void Widget_LineEdit::emit_textChanged()
{
    emit textChanged();
}











