#ifndef WINDOW_WELCOME_SETTING_H
#define WINDOW_WELCOME_SETTING_H

#include "window/smallWindow.h"

#include "widget/gradientButton.h"
#include "widget/roundButton.h"
#include "widget/chooseButton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/widget_dragstick.h"

#include "dataSet/cacheAgent.h"

class EditorSettingWindow : public SmallWindow
{
    Q_OBJECT

public:
    explicit EditorSettingWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    GradientButton *button_accept;
    GradientButton *button_cancel;

    ChooseButton *chooseButton_color;
    GradientButton *button_custom;

    Widget_DragStick *dragStick_scale_editor;
    Widget_DragStick *dragStick_scale_timeline;


    ChooseButton *chooseButton_antialising;
    //ChooseButton *chooseButton_tips;


public slots:
    void color_custom();

    void save();

};

#endif // WINDOW_WELCOME_SETTING_H
