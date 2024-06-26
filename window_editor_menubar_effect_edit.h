#ifndef WINDOW_EDITOR_MENUBAR_EFFECT_EDIT_H
#define WINDOW_EDITOR_MENUBAR_EFFECT_EDIT_H

#include "window_small.h"

#include "widget_lineEdit.h"
#include "widget_button.h"
#include "widget_roundbutton.h"
#include "widget_choosebutton.h"

#include "global.h"

class Window_editor_menubar_effect_edit0 : public Window_small
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_effect_edit0(Database *_db, DB_effect *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Database *db;
    DB_effect *file;

    Widget_LineEdit *lineEdit;

public slots:
    void end() override;

};

class Window_editor_menubar_effect_edit1 : public Window_small
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_effect_edit1(Database *_db, DB_effect *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Database *db;
    DB_effect *file;

    Widget_LineEdit *lineEdit;

public slots:
    void end() override;

};

class Window_editor_menubar_effect_edit2 : public Window_small
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_effect_edit2(Database *_db, DB_effect *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Database *db;
    DB_effect *file;

    Widget_LineEdit *lineEdit;

public slots:
    void end() override;

};


#endif // WINDOW_EDITOR_MENUBAR_HERO_EDIT_H
