#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include <QWidget>

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

#include "sprite.h"
#include <QSettings>

struct Col
{
    static QList<QColor> list;
    static void init();
    static void read();
    static void save();

#define Color(_col) Col::get(Col::_col)
#define ColorAlpha(_col,_alpha) Col::getAlpha(Col::_col,_alpha)
    inline static QColor get(int _col) { return list[_col]; }
    static QColor getAlpha(int _col, float _alpha);

#define ColorMix(_col1,_col2,_val) Col::mix(Col::_col1,Col::_col2,_val)
#define ColorMixAlpha(_col1,_col2,_val,_alpha) Col::mix(Col::_col1,Col::_col2,_val,_alpha)
    static QColor mix(int _col1, int _col2, float _val);
    static QColor mixAlpha(int _col1, int _col2, float _val, float _alpha);

    enum color {
        c_backgroundMain,
        c_backgroundSub,
        c_textMain,
        c_textTitle,
        c_symbol,
        c_theme,
        c_itemEdge,
        c_inactive
    };
};

struct Shd
{
    static QList<QOpenGLShaderProgram*> list;
    static void init();
    static void release();

    static int now;
    static bool isInited;

#define mkMat(_sx,_sy,_x,_y,_hw,_hh) Shd::_mkMat(_sx,_sy,_x,_y,_hw,_hh)
    inline static QMatrix4x4 _mkMat(float _scale_x, float _scale_y, float _x, float _y, float half_width, float half_height) {
        return QMatrix4x4(
                    _scale_x / half_width, 0, 0, -1 + _x / half_width,
                    0, -_scale_y / half_height, 0, 1 - _y / half_height,
                    0, 0, 1, 0, 0, 0, 0, 1);
    }

#define alphaModeEnable()  glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA)
#define alphaModeDisable() glDisable(GL_BLEND)

#define Shader(_shd) Shd::get(Shd::_shd)
    inline static QOpenGLShaderProgram* get(int _shd) { return list[_shd]; }
#define drawShaderBegin(_shd) Shd::list[Shd::_shd]->bind();Shd::now=Shd::_shd
#define shaderSetUniform(_name,_value) Shd::list[Shd::now]->setUniformValue(_name,_value)
#define drawShader(_size) glDrawArrays(GL_TRIANGLES,0,_size)
#define drawShaderEnd() Shd::list[Shd::now]->release();Shd::now=-1

    enum shader {
        Shd_Base,
        Shd_DrawTexture,
        Shd_DrawTextureWithMask
    };

};

struct Draw
{

    static QPainter *painter;
    static QFont font;
    static float font_scale;

    static int font_id;

    static QColor color1;
    static QColor color2;

    static void begin(QPaintDevice *_this);
    static void end();

    static void setAntialising(bool _flag = true);

    static void setColor(QColor _pen, QColor _brush);

#define setPenColor_c(_col) Draw::setPenColor(Color(_col))
#define setPenColor_ca(_col,_alpha) Draw::setPenColor(ColorAlpha(_col,_alpha))
#define setPenColor_m(_col1,_col2,_val) Draw::setPenColor(ColorMix(_col1,_col2,_val))
#define setPenColor_ma(_col1,_col2,_val_alpha) Draw::setPenColor(ColorMixAlpha(_col1,_col2,_val,_alpha))
#define setPenColor_false() Draw::setPenColor(0,0,0,0)
    static void setPenColor(int _r, int _g, int _b, int _a = 255);
    static void setPenColor(QColor _color);
    static void setPenColor(bool _isOpen);
    static void setPenLine(Qt::PenStyle = Qt::SolidLine);

#define setBrushColor_c(_col) Draw::setBrushColor(Color(_col))
#define setBrushColor_ca(_col,_alpha) Draw::setBrushColor(ColorAlpha(_col,_alpha))
#define setBrushColor_m(_col1,_col2,_val) Draw::setBrushColor(ColorMix(_col1,_col2,_val))
#define setBrushColor_ma(_col1,_col2,_val,_alpha) Draw::setBrushColor(ColorMixAlpha(_col1,_col2,_val,_alpha))
#define setBrushColor_false() Draw::setBrushColor(0,0,0,0)
    static void setBrushColor(int _r, int _g, int _b, int _a = 255);
    static void setBrushColor(QColor _color);
    static void setBrushColor(bool _isOpen);

    static void setTextDefault();
    static void setTextFont(QString _fontName);
    static void setTextSize(int _size);

    static void line(float _x1, float _y1, float _x2, float _y2, float _width = 1.0);
    static void line(QLineF _line, float _width = 1.0);
    static void lines(QLineF* _lines, int _count, float _width = 1.0);

    static void triangle(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3, float _width = 1.0);
    static void rect(float _x1, float _y1, float _x2, float _y2, float _width = 1.0);
    static void rect(QRect _rect, float _width = 1.0);
    static void roundRect(float _x1, float _y1, float _x2, float _y2, float _radius, float _width = 1.0);
    static void roundRect(QRect _rect, float _radius, float _width = 1.0);
    static void poly(QPolygonF _poly, float _width = 1.0);
    static void circle(float _x, float _y, float _radius, float _width = 1.0);

    static void fillet(float _x, float _y, float _radius, float _startAngle, float _endAngle, float _width = 1.0);
    static void pie(float _x, float _y, float _radius, float _startAngle, float _endAngle, float _width = 1.0);

    static void text(float _x, float _y, QString _text, Qt::Alignment _alignment = Qt::AlignCenter);
    static QString __tlwl_find(QString _str, QString _str_s, float _len_max, float _len_now = -1);
    static void text_line_with_length(float _x, float _y, QString _text, float _length, Qt::Alignment _alignment = Qt::AlignCenter);
    static void text(QRect _rect, QString _text, Qt::Alignment _alignment = Qt::AlignCenter);

    static void sprite(QPixmap _spr, float _x, float _y);
    static void sprite_ext(QPixmap _spr, float _x, float _y, float _xScale = 1.0, float _yScale = 1.0, float _xCenter = 0.0, float _yCenter = 0.0);
    static void sprite_size(QPixmap _spr, float _x, float _y, float _width, float _height);

    static void smallWindow(QPaintDevice *_this, QWidget *_window);

};

#endif // DRAW_H

