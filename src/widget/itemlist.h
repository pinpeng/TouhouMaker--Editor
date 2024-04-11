#ifndef ItemList_H
#define ItemList_H

#include <QWidget>
#include <QList>
#include <QMouseEvent>
#include <QWheelEvent>

struct itemSTR {
    QList<QString> text;

    itemSTR();
    itemSTR(QList<QString> _text);
};

class ItemList : public QWidget
{
    Q_OBJECT

public:
    explicit ItemList(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;



    int getHeadSize();

    void setHeadTextList(QList<QString> _text_list);
    void setHeadText(int _index, QString _text);

    QList<QString> getHeadTextList();
    QString getHeadText(int _index);

    void setHeadWidthList(QList<int> _width_list);
    void setHeadWidth(int _index, int _width);

    QList<int> getHeadWidthList();
    int getHeadWidth(int _index);

    void headClear();

    int getItemSize();

    void setItemList(QList<itemSTR> _item_list);
    void setItem(int _index, itemSTR _item);

    QList<itemSTR> getItemList();
    itemSTR getItem(int _index);

    void itemClear();

    int index();
    void resetIndex();
    void setIndex(int _index);

    void clear();

private:
    QList<QString> head_text;
    QList<int> head_width;

    QList<itemSTR> items;
    int item_index;

    float item_top;

signals:
    void select(int _index);
    void doubleClicked(int _index);

};

#endif // ItemList_H
