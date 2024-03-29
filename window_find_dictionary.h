#ifndef WINDOW_FIND_DICTIONARY_H
#define WINDOW_FIND_DICTIONARY_H

#include "window_small.h"
#include "widget_button.h"
#include "widget_lineEdit.h"
#include "widget_itemlist.h"

#include "global.h"

class Window_find_dictionary : public Window_small
{
    Q_OBJECT

public:

    explicit Window_find_dictionary(Database *_db, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:
    Database *db;

    Widget_LineEdit *lineEdit;
    Widget_Button *button_find;
    Widget_ItemList *itemList;

public slots:
    void find();
    void getPosition(int pos);

signals:
    void doubleClicked(int id);
};

#endif // WINDOW_FIND_DICTIONARY_H
