#ifndef WINDOW_EDITOR_MENUBAR_EFFECT_H
#define WINDOW_EDITOR_MENUBAR_EFFECT_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/widget_choosebutton.h"
#include "widget/widget_lineEdit.h"
#include "widget/widget_itemlist.h"

#include "global.h"

#include "window_editor_menubar_effect_edit.h"


class Window_editor_menubar_effect : public SmallWindow
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

    GradientButton *button_add;
    GradientButton *button_del;

    GradientButton *button_accept;
    GradientButton *button_cancel;

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
