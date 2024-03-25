#ifndef WINDOW_EDITOR_MENUBAR_BULLET_H
#define WINDOW_EDITOR_MENUBAR_BULLET_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/widget_lineEdit.h"
#include "widget/widget_itemlist.h"

#include "global.h"

#include "window_editor_menubar_bullet_edit.h"


class Window_editor_menubar_bullet : public SmallWindow
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

    GradientButton *button_add;
    GradientButton *button_del;

    GradientButton *button_accept;
    GradientButton *button_cancel;

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
