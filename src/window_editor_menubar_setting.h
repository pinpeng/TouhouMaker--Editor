#ifndef WINDOW_EDITOR_MENUBAR_SETTING_H
#define WINDOW_EDITOR_MENUBAR_SETTING_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/widget_itemlist.h"

#include "dataSet/cacheAgent.h"

#include "window_editor_menubar_setting_language.h"

class Window_editor_menubar_setting : public SmallWindow
{
    Q_OBJECT

public:

    explicit Window_editor_menubar_setting(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    /*QButtonGroup *buttonBox_start_with_logo;
    Widget_RoundButton *roundButton_swl_yes;
    Widget_RoundButton *roundButton_swl_no;*/

    /*QButtonGroup *buttonBox_reading_action;
    Widget_RoundButton *roundButton_ra_default;
    Widget_RoundButton *roundButton_ra_static;
    Widget_RoundButton *roundButton_ra_dynamic;
    Widget_RoundButton *roundButton_ra_custom;
    GradientButton *button_ra_custom;
    Window_editor_menubar_setting_ra *window_ra_custom;*/

    /*QButtonGroup *buttonBox_using_cg_collection;
    Widget_RoundButton *roundButton_ucc_yes;
    Widget_RoundButton *roundButton_ucc_no;*/

    EllipticalLineEdit *lineEdit_name;
    GradientButton *button_reset_name;

    Widget_ItemList *itemList_lan;

    GradientButton *button_lan_add;
    GradientButton *button_lan_del;
    Window_editor_menubar_setting_language *window_language;

    GradientButton *button_accept;
    GradientButton *button_cancel;

public slots:
    void updateList();
    void accept();

    void lan_add();
    void lan_del();
    void lan_edit(int pos);
    void lan_edit_finished();

    void reset_projectName();

    //void ra_custom();

};

#endif // WINDOW_EDITOR_MENUBAR_SETTING_H
