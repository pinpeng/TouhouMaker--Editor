#ifndef WINDOW_WELCOME_SETTING_H
#define WINDOW_WELCOME_SETTING_H

#include "window/smallWindow.h"

#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/widget_choosebutton.h"
#include "widget/widget_lineEdit.h"
#include "widget/widget_dragstick.h"

#include "global.h"

class Window_welcome_setting : public SmallWindow
{
    Q_OBJECT

public:
    explicit Window_welcome_setting(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    GradientButton *button_accept;
    GradientButton *button_cancel;

    Widget_ChooseButton *chooseButton_color;
    GradientButton *button_custom;

    Widget_DragStick *dragStick_scale_editor;
    Widget_DragStick *dragStick_scale_timeline;


    Widget_ChooseButton *chooseButton_antialising;
    //Widget_ChooseButton *chooseButton_tips;


public slots:
    void color_custom();

    void save();

};

#endif // WINDOW_WELCOME_SETTING_H
