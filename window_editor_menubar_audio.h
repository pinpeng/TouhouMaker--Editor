#ifndef WINDOW_EDITOR_MENUBAR_AUDIO_H
#define WINDOW_EDITOR_MENUBAR_AUDIO_H

#include "window_small.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_lineEdit.h"
#include "widget_itemlist.h"

#include "global.h"

#include "window_editor_menubar_audio_edit.h"

#include "window_find_audio.h"

class Window_editor_menubar_audio : public Window_small
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_audio(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    QButtonGroup *select_group;
    Widget_RoundButton *roundButton[3];

    Widget_Button *button_openFolder;

    Widget_ItemList *itemList;

    Widget_Button *button_add;
    Widget_Button *button_del;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    QString state_arr[2] = {"未保存", "已保存"};

    Window_editor_menubar_audio_edit *window_editor;

    void editAudioStart(int _index);

public slots:
    void updateList();
    void accept();

    void editAudio(int _index);
    void openFolder();

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_AUDIO_H
