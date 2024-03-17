#include "window_editor_menubar_effect_edit.h"

#include "message_box.h"

#include <QFileDialog>
#include <QDesktopServices>

Window_editor_menubar_effect_edit0::Window_editor_menubar_effect_edit0(Database *_db, DB_effect *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1400, 640);
    setWindowTitle("编辑子弹特效");

    db = _db;
    file = _file;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32 + 160, 64 + 80 * 0, 480, 80);
    lineEdit->setText(file->name);
}

void Window_editor_menubar_effect_edit0::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);


    Draw::end();
}

void Window_editor_menubar_effect_edit0::mousePressEvent(QMouseEvent *event)
{
    if(mousePressFunc(event)) return;
}

void Window_editor_menubar_effect_edit0::end()
{
    file->name = lineEdit->text();
    isClosing = true;
    emit closed();
}

Window_editor_menubar_effect_edit1::Window_editor_menubar_effect_edit1(Database *_db, DB_effect *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1400, 640);
    setWindowTitle("编辑场景特效");

    db = _db;
    file = _file;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32 + 160, 64 + 80 * 0, 480, 80);
    lineEdit->setText(file->name);
}

void Window_editor_menubar_effect_edit1::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);


    Draw::end();
}

void Window_editor_menubar_effect_edit1::mousePressEvent(QMouseEvent *event)
{
    if(mousePressFunc(event)) return;
}

void Window_editor_menubar_effect_edit1::end()
{
    file->name = lineEdit->text();
    isClosing = true;
    emit closed();
}


Window_editor_menubar_effect_edit2::Window_editor_menubar_effect_edit2(Database *_db, DB_effect *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1400, 640);
    setWindowTitle("编辑角色特效");

    db = _db;
    file = _file;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32 + 160, 64 + 80 * 0, 480, 80);
    lineEdit->setText(file->name);
}

void Window_editor_menubar_effect_edit2::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);


    Draw::end();
}

void Window_editor_menubar_effect_edit2::mousePressEvent(QMouseEvent *event)
{
    if(mousePressFunc(event)) return;
}

void Window_editor_menubar_effect_edit2::end()
{
    file->name = lineEdit->text();
    isClosing = true;
    emit closed();
}

