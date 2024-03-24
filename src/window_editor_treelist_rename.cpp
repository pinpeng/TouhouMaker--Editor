#include "window_editor_treelist_rename.h"

#include "global.h"

Window_editor_treelist_rename::Window_editor_treelist_rename(QString _text, int _id, QWidget *parent) : Window_small(parent)
{
    setFixedSize(640, 240);
    setWindowTitle("重命名");

    id = _id;
    name = _text;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32, 64, 640 - 64, 80);
    lineEdit->setText(_text);

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(80 - 8, 144, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(_timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(320 + 8, 144, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(_timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));
}

void Window_editor_treelist_rename::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_editor_treelist_rename::accept()
{
    if(name != lineEdit->text()) {
        Database db = Global::database();
        if(id >= 0) db.dialog_folder[id].name = lineEdit->text();
        else db.dialog_file[id].name = lineEdit->text();
        Global::databaseUpdate(db);
    }
    end();
}
