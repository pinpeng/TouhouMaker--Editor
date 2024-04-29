#ifndef WINDOW_EDITOR_MENUBAR_BULLET_H
#define WINDOW_EDITOR_MENUBAR_BULLET_H

#include "window_small.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_lineEdit.h"
#include "widget_itemlist.h"

#include "memoryCache/cacheAgent.h"

#include "window_editor_menubar_bullet_edit.h"


class Window_editor_menubar_bullet : public Window_small
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_bullet(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    QButtonGroup *select_group;
    Widget_RoundButton *roundButton[3];

    Widget_ItemList *itemList;

    Widget_Button *button_add;
    Widget_Button *button_del;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    Window_editor_menubar_bullet_edit *window_editor;


    void editBulletStart(int _index);

public slots:
    void updateList();
    void accept();

    void editBullet(int _index);

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_BULLET_H
