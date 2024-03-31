#include "draw.h"
#include "global.h"

#include <QFontDatabase>
#include "dataSet/editorSetting.h"

float Draw::font_scale = 1.0;
int Draw::font_id = 0;

QVector<QColor> Col::list = QVector<QColor>(static_cast<int>(Col::c_end));

void Col::init()
{    
    Col::list.resize(static_cast<int>(Col::c_end));
    Col::setThemeColor(Global::setting.themeColor());
}

void Col::setThemeColor(ThemeColor color){
    // TODO... 后续Draw当中的主题画笔配置，用json在外部记录
    switch (color) {
    case ThemeColor::DEFAULT:
        Col::list[Col::c_backgroundMain] =   QColor(255, 255, 255);
        Col::list[Col::c_backgroundSub] =    QColor(236, 236, 236);
        Col::list[Col::c_textMain] =         QColor(32, 32, 32);
        Col::list[Col::c_textTitle] =        QColor(64, 64, 64);
        Col::list[Col::c_symbol] =           QColor(192, 192, 192);
        Col::list[Col::c_theme] =            QColor(0, 128, 255);
        Col::list[Col::c_itemEdge] =         QColor(128, 128, 128);
        Col::list[Col::c_inactive] =         QColor(32, 32, 32);
        break;
    case ThemeColor::GRAY:
        Col::list[Col::c_backgroundMain] =    QColor(236, 236, 236);
        Col::list[Col::c_backgroundSub] =     QColor(212, 212, 212);
        Col::list[Col::c_textMain] =          QColor(0, 0, 0);
        Col::list[Col::c_textTitle] =         QColor(32, 32, 32);
        Col::list[Col::c_symbol] =            QColor(160, 160, 160);
        //Col::list[Col::c_theme] =             QColor(0, 108, 255);
        Col::list[Col::c_theme] =             QColor(0, 128, 255);
        Col::list[Col::c_itemEdge] =          QColor(108, 108, 108);
        Col::list[Col::c_inactive] =          QColor(16, 16, 16);
        break;
    case ThemeColor::DARK:
        Col::list[Col::c_backgroundMain] =    QColor(45, 45, 45);
        Col::list[Col::c_backgroundSub] =     QColor(32, 32, 32);
        Col::list[Col::c_textMain] =          QColor(224, 224, 224);
        Col::list[Col::c_textTitle] =         QColor(192, 192, 192);
        Col::list[Col::c_symbol] =            QColor(128, 128, 128);
        //Col::list[Col::c_theme] =             QColor(16, 144, 255);
        Col::list[Col::c_theme] =             QColor(0, 128, 255);
        Col::list[Col::c_itemEdge] =          QColor(160, 160, 160);
        Col::list[Col::c_inactive] =          QColor(128, 128, 128);
        break;
    case ThemeColor::CUSTOM:
        read();
        break;
    default:
        break;
    }
}

void Col::read()
{
    QSettings *file = new QSettings("color.ini", QSettings::IniFormat);
    int tmp;
    tmp = file->value("c/backgroundMain", 0xffffff).toUInt();
    list[c_backgroundMain] =    QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/backgroundSub", 0xf0f0f0).toUInt();
    list[c_backgroundSub] =     QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/textMain", 0x202020).toUInt();
    list[c_textMain] =          QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/textTitle", 0x000000).toUInt();
    list[c_textTitle] =         QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/symbol", 0x000000).toUInt();
    list[c_symbol] =            QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/theme", 0x0080ff).toUInt();
    list[c_theme] =             QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/itemEdge", 0x000000).toUInt();
    list[c_itemEdge] =          QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);
    tmp = file->value("c/inactive", 0x000000).toUInt();
    list[c_inactive] =          QColor((tmp / 65536) % 256, (tmp / 256) % 256, tmp % 256);

    delete file;
}

void Col::save()
{
    QSettings *file = new QSettings("color.ini", QSettings::IniFormat);
    file->setValue("c/backgroundMain", 0xffffff);
    file->setValue("c/backgroundSub", 0xf0f0f0);
    file->setValue("c/textMain", 0x202020);
    file->setValue("c/textTitle", 0x000000);
    file->setValue("c/symbol", 0x000000);
    file->setValue("c/theme", 0x0080ff);
    file->setValue("c/itemEdge", 0x000000);
    file->setValue("c/inactive", 0x000000);
    delete file;

}

QColor Col::getAlpha(int _col, float _alpha)
{
    QColor *col = &list[_col];
    return QColor(col->red(), col->green(), col->blue(), _alpha);
}

QColor Col::mix(int _col1, int _col2, float _val)
{
    QColor *c1 = &list[_col1];
    QColor *c2 = &list[_col2];
    return QColor(c1->red()   * (1.0 - _val) + c2->red() *_val,
                  c1->green() * (1.0 - _val) + c2->green() *_val,
                  c1->blue()  * (1.0 - _val) + c2->blue() *_val);
}

QColor Col::mixAlpha(int _col1, int _col2, float _val, float _alpha)
{
    QColor *c1 = &list[_col1];
    QColor *c2 = &list[_col2];
    return QColor(c1->red()   * (1.0 - _val) + c2->red() *_val,
                  c1->green() * (1.0 - _val) + c2->green() *_val,
                  c1->blue()  * (1.0 - _val) + c2->blue() *_val, _alpha);
}

// int Shd::now = -1;
// bool Shd::isInited = false;

// QList<QOpenGLShaderProgram*> Shd::list = QList<QOpenGLShaderProgram*>();

// void Shd::init()
// {
//     if(isInited) return;
//     isInited = true;
//     for(int i = 0; i < 2; i ++) list.append(new QOpenGLShaderProgram());

//     list[Shd_Base]->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shader/shd_base.vsh");
//     list[Shd_Base]->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shd_base.fsh");
//     list[Shd_Base]->link();

//     list[Shd_Base]->setAttributeBuffer("in_position", GL_FLOAT, 0 * sizeof(float), 2, 6 * sizeof(float));
//     list[Shd_Base]->enableAttributeArray("in_position");
//     list[Shd_Base]->setAttributeBuffer("in_color",    GL_FLOAT, 2 * sizeof(float), 4, 6 * sizeof(float));
//     list[Shd_Base]->enableAttributeArray("in_color");

//     list[Shd_DrawTexture]->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shader/shd_drawtexture.vsh");
//     list[Shd_DrawTexture]->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shd_drawtexture.fsh");
//     list[Shd_DrawTexture]->link();

//     list[Shd_DrawTexture]->setAttributeBuffer("in_position", GL_FLOAT, 0 * sizeof(float), 2, 2 * sizeof(float));
//     list[Shd_DrawTexture]->enableAttributeArray("in_position");

// }

// void Shd::release()
// {
//     if(!isInited) return;
//     for(int i = 0; i < list.size(); i ++) if(list[i]) delete list[i];
// }



QPainter*   Draw::painter = new QPainter();
QFont       Draw::font = QFont();

void Draw::begin(QPaintDevice *_this) {
    painter->begin(_this);
}

void Draw::end() {
    painter->end();
}

void Draw::setAntialising(bool _flag) {
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, _flag);
}


////////////////////////////////

void Draw::setColor(QColor _pen, QColor _brush)
{
    painter->setPen(_pen);
    painter->setBrush(_brush);
}

void Draw::setPenColor(int _r, int _g, int _b, int _a) {
    painter->setPen(QColor(_r, _g, _b, _a));
}

void Draw::setPenColor(QColor _color)
{
    painter->setPen(_color);
}

void Draw::setPenColor(bool _isOpen) {
    painter->setPen(_isOpen? QColor(0, 0, 0, 255): QColor(0, 0, 0, 0));
}

void Draw::setPenLine(Qt::PenStyle _style) {
    painter->setPen(QPen(painter->pen().color(), painter->pen().width(), _style));
}

void Draw::setBrushColor(int _r, int _g, int _b, int _a) {
    painter->setBrush(QColor(_r, _g, _b, _a));
}

void Draw::setBrushColor(QColor _color)
{
    painter->setBrush(_color);
}

void Draw::setBrushColor(bool _isOpen) {
    painter->setBrush(_isOpen? QColor(0, 0, 0, 255): QColor(0, 0, 0, 0));
}


////////////////////////////////

void Draw::setTextDefault()
{
//    font.setFamily("微软雅黑");
//    auto tmp = QFontDatabase::applicationFontFamilies(font_id);
//    font.setFamily(tmp[0]);
//    font.setPointSize(20 / font_scale);
}

void Draw::setTextFont(QString _fontName) {
    font.setFamily(_fontName);
}

void Draw::setTextSize(int _size) {
    font.setPointSize(_size / font_scale);
}

////////////////////////////////

void Draw::line(float _x1, float _y1, float _x2, float _y2, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    painter->drawLine(_x1, _y1, _x2, _y2);
}

void Draw::line(QLineF _line, float _width)
{
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    painter->drawLine(_line);
}

void Draw::lines(QLineF *_lines, int _count, float _width)
{
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    for(int i = 0; i < _count; i ++) painter->drawLine(_lines[i]);
}

void Draw::triangle(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    QPolygonF polygon;
    polygon.append(QPointF(_x1, _y1));
    polygon.append(QPointF(_x2, _y2));
    polygon.append(QPointF(_x3, _y3));
    painter->drawPolygon(polygon);
}

void Draw::rect(float _x1, float _y1, float _x2, float _y2, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    painter->drawRect(_x1, _y1, _x2 - _x1, _y2 - _y1);
}

void Draw::rect(QRect _rect, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    painter->drawRect(_rect);
}

void Draw::roundRect(float _x1, float _y1, float _x2, float _y2, float _radius, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    _radius *= _radius * 100;
    painter->drawRoundRect(_x1, _y1, _x2 - _x1, _y2 - _y1, _radius / abs(_x1 - _x2), _radius / abs(_y1 - _y2));
}

void Draw::roundRect(QRect _rect, float _radius, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    _radius *= _radius * 100;
    painter->drawRoundRect(_rect, _radius / _rect.width(), _radius / _rect.height());
}

void Draw::poly(QPolygonF _poly, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    painter->drawPolygon(_poly);
}

void Draw::circle(float _x, float _y, float _radius, float _width)
{
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    painter->drawEllipse(_x - _radius, _y - _radius, _radius * 2.0, _radius * 2.0);
}

void Draw::fillet(float _x, float _y, float _radius, float _startAngle, float _endAngle, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    QRect rect = QRect(_x - _radius, _y - _radius, _radius * 2.0, _radius * 2.0);
    painter->drawArc(rect, _startAngle * 16.0, (_endAngle - _startAngle) * 16.0);
}

void Draw::pie(float _x, float _y, float _radius, float _startAngle, float _endAngle, float _width) {
    painter->setPen(QPen(painter->pen().color(), _width, painter->pen().style()));
    QRect rect = QRect(_x - _radius, _y - _radius, _radius * 2.0, _radius * 2.0);
    painter->drawPie(rect, _startAngle * 16.0, (_endAngle - _startAngle) * 16.0);
}

////////////////////////////////

void Draw::text(float _x, float _y, QString _text, Qt::Alignment _alignment) {
    painter->setFont(font);
    QRectF text_rect = painter->boundingRect(QRectF(), true, _text);
    float text_width = text_rect.width();
    float text_height = text_rect.height();
    QRect rect(_x - text_width / 2, _y - text_height / 2, text_width, text_height);
    if(_alignment & Qt::AlignLeft) { rect.setX(_x); rect.setWidth(text_width); }
    if(_alignment & Qt::AlignRight) { rect.setX(_x - text_width); rect.setWidth(text_width); }
    if(_alignment & Qt::AlignTop) { rect.setY(_y); rect.setHeight(text_height); }
    if(_alignment & Qt::AlignBottom) { rect.setY(_y - text_height); rect.setHeight(text_height); }
    painter->drawText(rect, _alignment, _text);
}

QString Draw::__tlwl_find(QString _str, QString _str_s, float _len_max, float _len_now)
{
    float text_width = _len_now;
    if(_len_now == -1) {
        QRectF text_rect = painter->boundingRect(QRectF(), true, _str);
        text_width = text_rect.width();
    }
    //qDebug() << "this" << _str << text_width << _len_max;
    if(text_width > _len_max * 2) return __tlwl_find(_str_s.left(_str.length() / 2), _str_s, _len_max);
    if(abs(text_width - _len_max) < 4) return _str;
    if(text_width < _len_max) {
        if(_str.length() == _str_s.length()) return _str;
        QString str_next = _str_s.left(_str.length() + 1);
        float text_width_next = text_width + QFontMetricsF(font).width(str_next.right(1));
        if(text_width_next < _len_max) {
            if(_str.length() + 1 >= _str_s.length()) return str_next;
            else return __tlwl_find(str_next, _str_s, _len_max, text_width_next);
        } else return _str;
    } else return __tlwl_find(_str_s.left(qMax(_str.length() - 6, 1)), _str_s, _len_max);
}

void Draw::text_line_with_length(float _x, float _y, QString _text, float _length, Qt::Alignment _alignment)
{
    painter->setFont(font);
    _text = _text.replace("\n", "\\n");
    QString str = __tlwl_find(_text, _text, _length);
    if(str.length() < _text.length()) str = str + "...";
    QRectF text_rect = painter->boundingRect(QRectF(), true, str);
    float text_height = text_rect.height();
    float text_width = text_rect.width();
    QRect rect(_x - text_width / 2, _y - text_height / 2, text_width, text_height);
    if(_alignment & Qt::AlignLeft) { rect.setX(_x); rect.setWidth(text_width); }
    if(_alignment & Qt::AlignRight) { rect.setX(_x - text_width); rect.setWidth(text_width); }
    if(_alignment & Qt::AlignTop) { rect.setY(_y); rect.setHeight(text_height); }
    if(_alignment & Qt::AlignBottom) { rect.setY(_y - text_height); rect.setHeight(text_height); }
    painter->drawText(rect, _alignment, str);
}

void Draw::text(QRect _rect, QString _text, Qt::Alignment _alignment) {
    painter->setFont(font);
    painter->drawText(_rect, _alignment, _text);
}

////////////////////////////////

void Draw::sprite(QPixmap _spr, float _x, float _y) {
    painter->drawPixmap(_x, _y, _spr);
}

void Draw::sprite_ext(QPixmap _spr, float _x, float _y, float _xScale, float _yScale, float _xCenter, float _yCenter)
{
    float w = _spr.width() * _xScale;
    float h = _spr.height() * _yScale;
    painter->drawTiledPixmap(_x - w / 2 - _xCenter * w, _y - h / 2 - _yCenter * h, w, h, _spr);
}

void Draw::sprite_size(QPixmap _spr, float _x, float _y, float _width, float _height)
{
    painter->drawTiledPixmap(_x, _y, _width, _height, _spr.scaled(_width, _height));
}

void Draw::smallWindow(QPaintDevice *_this, QWidget *_window)
{

    float w_l = _window->rect().x() + 8;
    float w_r = _window->rect().right() - 8;
    float w_t = _window->rect().y() + 8;
    float w_b = _window->rect().bottom() - 8;

    begin(_this);
    setAntialising(true);

    if(_window->isActiveWindow()) setPenColor(Color(c_theme));
    else setPenColor(Color(c_itemEdge));
    setBrushColor(Color(c_backgroundMain));
    roundRect(w_l, w_t, w_r, w_b, 8, 3);

    setPenColor(Color(c_inactive));
    line(w_l + 12, w_t + 48, w_r - 8, w_t + 48, 1);

    setTextDefault();
    setTextSize(18);
    setPenColor(Color(c_textTitle));
    text(w_l + 32, w_t + 24 + 2, _window->windowTitle(), Qt::AlignLeft | Qt::AlignVCenter);

    Draw::end();
}






















