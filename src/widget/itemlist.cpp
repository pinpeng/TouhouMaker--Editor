#include "widget/itemlist.h"


#include "draw.h"

itemSTR::itemSTR()
{

}

itemSTR::itemSTR(QList<QString> _text)
{
    text.append(_text);
}

ItemList::ItemList(QWidget *parent) : QWidget(parent)
{
    resetIndex();
}

void ItemList::paintEvent(QPaintEvent *)
{
    float w_l = rect().x() + 12;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;

    Draw::begin(this);
    Draw::setAntialising();

    setPenColor_c(c_itemEdge);
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(w_l, w_t, w_r, w_b, 4, 2);

    w_l += 8;
    w_t += 4;

    Draw::setTextDefault();
    int width_sum = w_l;

    for(int i = 0; i < qMin(head_text.size(), head_width.size()); i ++) {
        if(i < head_text.size() - 1) {
            setPenColor_c(c_theme);
            Draw::text(width_sum + head_width[i] / 2, w_t + 24 + 4, head_text[i]);
            setPenColor_c(c_symbol);
            width_sum += head_width[i];
            Draw::line(4 + width_sum, w_t + 4, 4 + width_sum, w_t + 48, 2);
        } else {
            setPenColor_c(c_theme);
            Draw::text((width_sum + w_r) / 2.0, w_t + 24 + 4, head_text[i]);
        }
    }

    setPenColor_c(c_symbol);
    Draw::line(rect().x() + 20, w_t + 56, w_r - 8, w_t + 56, 2);

    w_t += 64;
    w_r -= 16;

    int size_max = items.size();

    if(!size_max) {
        setPenColor_c(c_textMain);
        Draw::text(rect().x() + 32, w_t, "无项目", Qt::AlignLeft | Qt::AlignTop);
    } else {

        int show_max = (w_b - w_t) / 48;
        item_top = qMax(float(0.0), qMin(float(item_top), float(size_max - show_max)));
        int num = item_top;

        setPenColor_c(c_textMain);
        Draw::setTextDefault();

        for(int i = 0; i < qMin(size_max, show_max); i ++) {
            if(num == item_index) {
                setPenColor_c(c_theme);
                setBrushColor_ca(c_theme, 32);
                Draw::rect(rect().x() + 20, w_t + i * 48, w_r - 8, w_t + i * 48 + 48, 2);

            }

            itemSTR *tmp = &items[num++];
            width_sum = w_l;
            setPenColor_c(c_textMain);

            for(int j = 0; j < head_text.size(); j ++) {
                if(j < head_text.size() - 1) {
                    Draw::text_line_with_length(width_sum + head_width[j] / 2, w_t + i * 48 + 24 + 2, tmp->text[j], head_width[j] - 32, Qt::AlignCenter);
                    width_sum += head_width[j];
                } else {
                    Draw::text_line_with_length((width_sum + w_r) / 2.0, w_t + i * 48 + 24 + 2, tmp->text[j], (w_r - width_sum) - 32, Qt::AlignCenter);
                }
            }
        }

        setPenColor_false();
        setBrushColor_c(c_symbol);
        Draw::circle(w_r + 4, w_t + 4, 4);
        Draw::rect(w_r, w_t + 4, w_r + 8, w_b - 12);
        Draw::circle(w_r + 4, w_b - 12, 4);

        setBrushColor_c(c_theme);
        float h = (w_b - w_t - 16);
        float t = w_t + 4 + h * (item_top / size_max);
        float b = w_t + 4 + h * qMin(float(1.0), float((item_top + show_max) / size_max));
        Draw::circle(w_r + 4, t, 4);
        Draw::rect(w_r, t, w_r + 8, b);
        Draw::circle(w_r + 4, b, 4);

    }

    Draw::end();
}

void ItemList::mousePressEvent(QMouseEvent *event)
{
    int size_max = items.size();
    if(!size_max) return;
    float w_t = rect().y() + 80;
    float w_b = w_t + int((rect().bottom() - 8 - w_t) / 48) * 48;

    float my = event->pos().y();
    if(w_t < my && my < w_b) {
        int tmp = (my - w_t) / 48;
        if(tmp + item_top >= size_max) {
            item_index = -1;
            emit select(-1);
        } else {
            item_index = tmp + item_top;
            emit select(item_index);
        }
    } else {
        item_index = -1;
        emit select(-1);
    }
    repaint();
}

void ItemList::mouseDoubleClickEvent(QMouseEvent *event)
{
    int size_max = items.size();
    if(!size_max) return;
    if(event->button() == Qt::LeftButton) {
        float w_t = rect().y() + 80;
        float w_b = w_t + int((rect().bottom() - 8 - w_t) / 48) * 48;

        float my = event->pos().y();
        if(w_t < my && my < w_b && item_index == int((my - w_t) / 48 + int(item_top))) {
            emit doubleClicked(item_index);
        }
    }
}

void ItemList::wheelEvent(QWheelEvent *event)
{
    item_top -= event->angleDelta().y() / 120;
    if(item_top < 0) item_top = 0;
    repaint();
}

int ItemList::getHeadSize()
{
    return head_text.size();
}

void ItemList::setHeadTextList(QList<QString> _text_list)
{
    item_index = -1;
    head_text.clear();
    head_text.append(_text_list);
    repaint();
}

void ItemList::setHeadText(int _index, QString _text)
{
    head_text[_index] = _text;
    repaint();
}

QList<QString> ItemList::getHeadTextList()
{
    return head_text;
}

QString ItemList::getHeadText(int _index)
{
    return head_text[_index];
}

void ItemList::setHeadWidthList(QList<int> _width_list)
{
    item_index = -1;
    head_width.clear();
    head_width.append(_width_list);
    repaint();
}

void ItemList::setHeadWidth(int _index, int _width)
{
    head_width[_index] = _width;
    repaint();
}

QList<int> ItemList::getHeadWidthList()
{
    return head_width;
}

int ItemList::getHeadWidth(int _index)
{
    return head_width[_index];
}

void ItemList::headClear()
{
    head_text.clear();
    head_width.clear();
    repaint();
}

int ItemList::getItemSize()
{
    return items.size();
}

void ItemList::setItemList(QList<itemSTR> _item_list)
{
    item_index = -1;
    items.clear();
    items.append(_item_list);
    repaint();
}

void ItemList::setItem(int _index, itemSTR _item)
{
    items[_index] = _item;
    repaint();
}

QList<itemSTR> ItemList::getItemList()
{
    return items;
}

itemSTR ItemList::getItem(int _index)
{
    return items[_index];
}

void ItemList::itemClear()
{
    item_index = -1;
    items.clear();
    repaint();
}

int ItemList::index()
{
    return item_index;
}

void ItemList::resetIndex()
{
    item_index = -1;
    emit select(-1);
}

void ItemList::setIndex(int _index)
{
     item_index = _index;
     item_top = _index;
     emit select(item_index);
}

void ItemList::clear()
{
    headClear();
    itemClear();
    item_index = -1;
}

