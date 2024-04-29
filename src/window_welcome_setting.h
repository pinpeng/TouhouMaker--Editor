#ifndef WINDOW_WELCOME_SETTING_H
#define WINDOW_WELCOME_SETTING_H

#include "window_small.h"

#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_choosebutton.h"
#include "widget_lineEdit.h"
#include "widget_dragstick.h"

#include "memoryCache/cacheAgent.h"

class Window_welcome_setting : public Window_small
{
    Q_OBJECT

public:
    explicit Window_welcome_setting(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    Widget_ChooseButton *chooseButton_color;
    Widget_Button *button_custom;

    Widget_DragStick *dragStick_scale_editor;
    Widget_DragStick *dragStick_scale_timeline;


    Widget_ChooseButton *chooseButton_antialising;
    //Widget_ChooseButton *chooseButton_tips;


public slots:
    void color_custom();

    void save();

};

#endif // WINDOW_WELCOME_SETTING_H
