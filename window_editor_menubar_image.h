#ifndef WINDOW_EDITOR_MENUBAR_IMAGE_H
#define WINDOW_EDITOR_MENUBAR_IMAGE_H

#include "window/smallWindow.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_lineEdit.h"
#include "widget_itemlist.h"

#include "global.h"

#include "window_editor_menubar_image_edit.h"

#include "window_find.h"

class Window_editor_menubar_image : public SmallWindow
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_image(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    QButtonGroup *select_group;
    Widget_RoundButton *roundButton[4];

    Widget_Button *button_openFolder;

    Widget_ItemList *itemList;

    Widget_Button *button_add;
    Widget_Button *button_del;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    QString state_arr[3] = {"未保存", "已保存", "已保存"};

    QLabel *label;

    Window_editor_menubar_image_edit *window_editor;

    void editAudioStart(int _index);

public slots:
    void updateList();
    void accept();

    void editAudio(int _index);
    void openFolder();

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_IMAGE_H
