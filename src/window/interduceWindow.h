#ifndef WINDOW_WELCOME_MAIN_H
#define WINDOW_WELCOME_MAIN_H

#include "widget/gradientButton.h"

#include "window/smallWindow.h"
#include "window_welcome_newproject.h"
#include "window_welcome_setting.h"

#include "window_editor_main.h"

#include "draw.h"

class InterduceWindow : public SmallWindow
{
    Q_OBJECT

public:

    explicit InterduceWindow(QWidget *parent = nullptr);
    ~InterduceWindow();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);


private slots:
    void newProjectSlot();
    void openProjectSlot();
    void settingSlot();
    void helpSlot();

    void newStartSlot();
    void openStartSlot();

private:

    bool show_last = false;
    QString show_last_name;

    GradientButton *_newProjectButton;
    GradientButton *_openProjectButton;
    GradientButton *_settingButton;
    GradientButton *_helpButton;


    Window_welcome_newProject *win_newProj;
    Window_welcome_setting *win_setting;

    Window_editor_main *win_editor;

};

#endif // WINDOW_WELCOME_MAIN_H
