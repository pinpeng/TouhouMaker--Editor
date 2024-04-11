#ifndef WINDOW_EDITOR_MENUBAR_SETTING_LANGUAGE_H
#define WINDOW_EDITOR_MENUBAR_SETTING_LANGUAGE_H

#include "window/smallWindow.h"

#include "widget/ellipticalLineEdit.h"
#include "widget/gradientButton.h"
#include "widget/roundButton.h"

#include "dataSet/cacheAgent.h"

class Window_editor_menubar_setting_language : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_setting_language(QString *_str, QWidget *parent = nullptr);

private:
    QString *str;

    EllipticalLineEdit *lineEdit;

    GradientButton *button_accept;
    GradientButton *button_cancel;

public slots:
    void accept();

signals:
    void changed();

};

#endif // WINDOW_EDITOR_MENUBAR_SETTING_LANGUAGE_H
