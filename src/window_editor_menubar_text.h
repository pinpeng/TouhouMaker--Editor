#ifndef WINDOW_EDITOR_MENUBAR_TEXT_H
#define WINDOW_EDITOR_MENUBAR_TEXT_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/widget_lineEdit.h"
#include "widget/widget_textEdit.h"
#include "widget/widget_itemlist.h"

#include "widget/widget_choosebutton.h"
#include "window_ask.h"

#include "global.h"

class Window_editor_menubar_text_edit : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_text_edit(Database *_db, DB_text *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

private:
    Database *db;
    DB_text *file;

    int language_last = 0;
    Widget_ChooseButton *chooseButton_language;

    Widget_TextEdit *textEdit;

public slots:
    void end() override;

    void languageChanged(int _index);

};

class Window_editor_menubar_text : public SmallWindow
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_text(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    Widget_ChooseButton *chooseButton;

    Widget_ItemList *itemList;

    GradientButton *button_accept;
    GradientButton *button_cancel;

    Window_editor_menubar_text_edit *window_editor;

    void editAudioStart(int _index);

public slots:
    void updateList();
    void accept();

    void editAudio(int _index);

};

#endif // WINDOW_EDITOR_MENUBAR_TEXT_H
