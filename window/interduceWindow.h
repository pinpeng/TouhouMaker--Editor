#ifndef INTERDUCE_WINDOW_H
#define INTERDUCE_WINDOW_H

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
    ~InterduceWindow() = default;

//    void paintEvent(QPaintEvent *);
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

    GradientButton *buttonNewProj;
    GradientButton *buttonOpenProj;
    GradientButton *buttonSetting;
    GradientButton *buttonHelp;


    Window_welcome_newProject *win_newProj;
    Window_welcome_setting *win_setting;

    Window_editor_main *win_editor;

};

#endif // INTERDUCE_WINDOW_H
