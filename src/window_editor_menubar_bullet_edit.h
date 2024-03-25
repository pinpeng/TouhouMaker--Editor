#ifndef WINDOW_EDITOR_MENUBAR_BULLET_EDIT_H
#define WINDOW_EDITOR_MENUBAR_BULLET_EDIT_H

#include "window/smallWindow.h"

#include "widget/widget_lineEdit.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/widget_choosebutton.h"

#include "global.h"

class Window_editor_menubar_bullet_edit : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_bullet_edit(Database *_db, DB_bullet *_file, int _group, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    Database *db;
    DB_bullet *file;
    QLabel *label;

    int group;

    Widget_LineEdit *lineEdit_name;
    Widget_ChooseButton *chooseButton_type;
    Widget_ChooseButton *chooseButton_range;
    Widget_LineEdit *lineEdit_collision;

    float code_scroll_top = 0;

public slots:
    void end() override;

    void updateData();
    void updateImage();

};

#endif // WINDOW_EDITOR_MENUBAR_HERO_BULLET_H
