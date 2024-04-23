#ifndef WINDOW_EDITOR_MENUBAR_EFFECT_H
#define WINDOW_EDITOR_MENUBAR_EFFECT_H

#include "window_small.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_choosebutton.h"
#include "widget_lineEdit.h"
#include "widget_itemlist.h"

#include "global.h"

#include "window_editor_menubar_effect_edit.h"


class Window_editor_menubar_effect : public Window_small
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_effect(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    Widget_ItemList *itemList;

    QButtonGroup *select_group;
    Widget_RoundButton *roundButton[3];

    Widget_Button *button_add;
    Widget_Button *button_del;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    Window_editor_menubar_effect_edit0 *window_editor0;
    Window_editor_menubar_effect_edit1 *window_editor1;
    Window_editor_menubar_effect_edit2 *window_editor2;

    void editHeroStart(int _index);

public slots:
    void updateList();
    void accept();

    void editHero(int _index);

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_EFFECT_H
