#include "widget/ellipticalLineEdit.h"

#include "draw.h"

EllipticalLineEdit::EllipticalLineEdit(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(80);
    Draw::setTextDefault();
    _lebel = new QLineEdit(this);
    _lebel->setGeometry(rect().left() + 24, rect().top(), rect().width() - 48, rect().height());
    _lebel->setFont(Draw::font);
    _lebel->setAttribute(Qt::WA_TranslucentBackground);
    _lebel->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent;color:rgb(" +
                         QString::number(Color(c_textMain).red()) + "," +
                         QString::number(Color(c_textMain).green()) + "," +
                         QString::number(Color(c_textMain).blue()) + ")}");
    _lebel->show();

    connect(_lebel, SIGNAL(textChanged(QString)), this, SLOT(textChangedSlot()));
}

EllipticalLineEdit::EllipticalLineEdit(const QString& text,const QRect& rect,QWidget *parent) : EllipticalLineEdit(parent)
{
    setText(text);
    setGeometry(rect);
}

void EllipticalLineEdit::paintEvent(QPaintEvent *) {
    _lebel->setGeometry(rect().left() + 24, rect().top(), rect().width() - 48, rect().height());

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

void EllipticalLineEdit::setText(QString _text) {
    _lebel->setText(_text);
}

QString EllipticalLineEdit::text() {
    return _lebel->text();
}

void EllipticalLineEdit::textChangedSlot()
{
    emit textChanged();
}











