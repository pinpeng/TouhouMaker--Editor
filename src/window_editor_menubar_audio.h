#ifndef WINDOW_EDITOR_MENUBAR_AUDIO_H
#define WINDOW_EDITOR_MENUBAR_AUDIO_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/widget_itemlist.h"

#include "dataSet/cacheAgent.h"

#include "window_editor_menubar_audio_edit.h"

#include "window_find_audio.h"

class Window_editor_menubar_audio : public SmallWindow
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_audio(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    QButtonGroup *select_group;
    Widget_RoundButton *roundButton[3];

    GradientButton *button_openFolder;

    Widget_ItemList *itemList;

    GradientButton *button_add;
    GradientButton *button_del;

    GradientButton *button_accept;
    GradientButton *button_cancel;

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
