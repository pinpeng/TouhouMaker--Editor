#ifndef WINDOW_EDITOR_MENUBAR_SETTING_LANGUAGE_H
#define WINDOW_EDITOR_MENUBAR_SETTING_LANGUAGE_H

#include "window/smallWindow.h"

#include "widget/widget_lineEdit.h"
#include "widget/widget_button.h"
#include "widget/widget_roundbutton.h"

#include "global.h"

class Window_editor_menubar_setting_language : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_setting_language(QString *_str, QWidget *parent = nullptr);

private:
    QString *str;

    Widget_LineEdit *lineEdit;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

public slots:
    void accept();

signals:
    void changed();

};

#endif // WINDOW_EDITOR_MENUBAR_SETTING_LANGUAGE_H
