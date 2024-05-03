#ifndef WINDOW_EDITOR_MENUBAR_TEXT_H
#define WINDOW_EDITOR_MENUBAR_TEXT_H

#include "window_small.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_lineEdit.h"
#include "widget_textEdit.h"
#include "widget_itemlist.h"

#include "widget_choosebutton.h"
#include "window_ask.h"

#include "memoryCache/cacheAgent.h"

class Window_editor_menubar_text_edit : public Window_small
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_text_edit(ProjectData *_db, DB_text *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

private:
    ProjectData *db;
    DB_text *file;

    int language_last = 0;
    Widget_ChooseButton *chooseButton_language;

    Widget_TextEdit *textEdit;

public slots:
    void end() override;

    void languageChanged(int _index);

};

class Window_editor_menubar_text : public Window_small
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_text(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    ProjectData db;

    Widget_ChooseButton *chooseButton;

    Widget_ItemList *itemList;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    Window_editor_menubar_text_edit *window_editor;

    void editAudioStart(int _index);

public slots:
    void updateList();
    void accept();

    void editAudio(int _index);

};

#endif // WINDOW_EDITOR_MENUBAR_TEXT_H
