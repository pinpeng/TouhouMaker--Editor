//#include "widget/gradientShadowButton.h"

//GradientShadowButton::GradientShadowButton(QWidget *parent) : GradientButton(parent)
//{
//    effect = new QGraphicsDropShadowEffect();
//    effect->setBlurRadius(8);
//    effect->setColor(QColor(0, 0, 0, 128));
//    effect->setOffset(0, 0);
//    setGraphicsEffect(effect);
//}

//void Widget_ButtonShadow::paintEvent(QPaintEvent *)
//{
//    float w_l = rect().x() + 12;
//    float w_r = rect().right() - 8;
//    float w_t = rect().y() + 8;
//    float w_b = rect().bottom() - 8;
//    float w_h = (w_b - w_t) / 2;

//    float _alpha = getAlpha();
//    QString _text = getText();

//    Draw::begin(this);
//    Draw::setAntialising(true);

//    setPenColor_false();
//    setBrushColor_m(c_backgroundMain, c_textMain, _alpha);
//    Draw::pie(w_l + w_h, w_t + w_h, w_h, 90, 270);
//    Draw::pie(w_r - w_h, w_t + w_h, w_h, 270, 450);
//    Draw::rect(w_l + w_h, w_t, w_r - w_h + 1, w_b);

//    setPenColor_m(c_textMain, c_backgroundMain, _alpha);
//    Draw::setTextDefault();
//    Draw::text(rect().center().x(), rect().center().y() + 2, _text, Qt::AlignCenter);
//    Draw::end();
//}
