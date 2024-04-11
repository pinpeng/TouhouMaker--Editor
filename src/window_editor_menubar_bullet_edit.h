#ifndef WINDOW_EDITOR_MENUBAR_BULLET_EDIT_H
#define WINDOW_EDITOR_MENUBAR_BULLET_EDIT_H

#include "window/smallWindow.h"

#include "widget/ellipticalLineEdit.h"
#include "widget/gradientButton.h"
#include "widget/roundButton.h"
#include "widget/chooseButton.h"

#include "dataSet/cacheAgent.h"

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

    EllipticalLineEdit *lineEdit_name;
    ChooseButton *chooseButton_type;
    ChooseButton *chooseButton_range;
    EllipticalLineEdit *lineEdit_collision;

    float code_scroll_top = 0;

public slots:
    void end() override;

    void updateData();
    void updateImage();

};

#endif // WINDOW_EDITOR_MENUBAR_HERO_BULLET_H
