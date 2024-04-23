#include "window_editor_menubar_setting_language.h"

#include "global.h"

Window_editor_menubar_setting_language::Window_editor_menubar_setting_language(QString *_str, QWidget *parent) : Window_small(parent)
{
    setFixedSize(640, 240);
    setWindowTitle("重命名语言");

    str = _str;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32, 64, 640 - 64, 80);
    lineEdit->setText(*str);

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(80 - 8, 144, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(320 + 8, 144, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));
}

void Window_editor_menubar_setting_language::accept()
{
    if(lineEdit->text().size() > 9) {
        Message("名称太长啦");
        return;
    }
    *str = lineEdit->text();
    emit changed();
    end();
}


