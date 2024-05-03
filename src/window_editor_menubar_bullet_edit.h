#ifndef WINDOW_EDITOR_MENUBAR_BULLET_EDIT_H
#define WINDOW_EDITOR_MENUBAR_BULLET_EDIT_H

#include "window_small.h"

#include "widget_lineEdit.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_choosebutton.h"

#include "memoryCache/cacheAgent.h"

class Window_editor_menubar_bullet_edit : public Window_small
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_bullet_edit(ProjectData *_db, DB_bullet *_file, int _group, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    ProjectData *db;
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
