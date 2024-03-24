#ifndef WINDOW_WELCOME_MAIN_H
#define WINDOW_WELCOME_MAIN_H

#include "widget/widget_button.h"

#include "window/smallWindow.h"
#include "window_welcome_newproject.h"
#include "window_welcome_setting.h"

#include "window_editor_main.h"

#include "draw.h"

class Window_welcome_main : public SmallWindow
{
    Q_OBJECT

public:

    explicit Window_welcome_main(QWidget *parent = nullptr);
    ~Window_welcome_main();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);


private slots:
    void newProj();
    void openProj();
    void setting();
    void help();

    void newStart();
    void openStart();

private:

    bool show_last = false;
    QString show_last_name;

    Widget_Button *buttonNewProj;
    Widget_Button *buttonOpenProj;
    Widget_Button *buttonSetting;
    Widget_Button *buttonHelp;


    Window_welcome_newProject *win_newProj;
    Window_welcome_setting *win_setting;

    Window_editor_main *win_editor;

};

#endif // WINDOW_WELCOME_MAIN_H
