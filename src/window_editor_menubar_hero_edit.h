#ifndef WINDOW_EDITOR_MENUBAR_HERO_EDIT_H
#define WINDOW_EDITOR_MENUBAR_HERO_EDIT_H

#include "window/smallWindow.h"

#include "widget/ellipticalLineEdit.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"
#include "widget/widget_choosebutton.h"

#include "dataSet/cacheAgent.h"

class Window_editor_menubar_hero_edit0 : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_hero_edit0(Database *_db, DB_hero *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    // void mousePressEvent(QMouseEvent *event) override;

private:
    Database *db;
    DB_hero *file;

    int language_last = 0;
    Widget_ChooseButton *chooseButton_language;
    EllipticalLineEdit *lineEdit;

    Widget_ChooseButton *chooseButton_bullet;
    GradientButton *button_bullet1;
    GradientButton *button_bullet2;
    Widget_ChooseButton *chooseButton_skill;
    GradientButton *button_skill1;
    GradientButton *button_skill2;
    EllipticalLineEdit *lineEdit_s1;
    EllipticalLineEdit *lineEdit_s2;

public slots:
    void end() override;

    void languageChanged(int _index);

};

class Window_editor_menubar_hero_edit1 : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_hero_edit1(Database *_db, DB_enemy *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    Database *db;
    DB_enemy *file;

    QLabel *label;

    EllipticalLineEdit *lineEdit_name;
    EllipticalLineEdit *lineEdit_hp;
    Widget_ChooseButton *chooseButton_range;
    EllipticalLineEdit *lineEdit_collision;

    float code_scroll_top = 0;

    EllipticalLineEdit *lineEdit;

public slots:
    void end() override;

    void updateData();

};

class Window_editor_menubar_hero_edit2 : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_hero_edit2(Database *_db, DB_boss *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Database *db;
    DB_boss *file;

    QLabel *label[3];

    int language_last = 0;
    Widget_ChooseButton *chooseButton_language;
    EllipticalLineEdit *lineEdit;

public slots:
    void end() override;

    void languageChanged(int _index);


};


#endif // WINDOW_EDITOR_MENUBAR_HERO_EDIT_H
