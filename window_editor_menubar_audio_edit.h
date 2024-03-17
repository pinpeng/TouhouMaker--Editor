#ifndef WINDOW_EDITOR_MENUBAR_AUDIO_EDIT_H
#define WINDOW_EDITOR_MENUBAR_AUDIO_EDIT_H

#include "window/smallWindow.h"

#include "widget_lineEdit.h"
#include "widget_button.h"
#include "widget_roundbutton.h"

#include "global.h"

class Window_editor_menubar_audio_edit : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_audio_edit(Database *_db, DB_audio *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

private:
    Database *db;
    DB_audio *file;

    Widget_LineEdit *lineEdit;
    Widget_Button *button_open;
    Widget_Button *button_preview;

    QString state_arr[2] = {"未保存", "已保存"};

public slots:
    void end() override;

    void open();
    void preview();

};

#endif // WINDOW_EDITOR_MENUBAR_AUDIO_EDIT_H
