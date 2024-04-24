#ifndef WINDOW_EDITOR_TREELIST_RENAME_H
#define WINDOW_EDITOR_TREELIST_RENAME_H

#include "window_small.h"
#include "widget_button.h"
#include "widget_lineEdit.h"

class Window_editor_treelist_rename : public Window_small
{
    Q_OBJECT

public:

    explicit Window_editor_treelist_rename(QString _text, int _id, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:
    int id;
    QString name;
    Widget_LineEdit *lineEdit;
    Widget_Button *button_accept;
    Widget_Button *button_cancel;

public slots:
    void accept();

};

#endif // WINDOW_EDITOR_TREELIST_RENAME_H
