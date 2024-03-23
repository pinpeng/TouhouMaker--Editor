#ifndef WINDOW_FIND_IMAGE_H
#define WINDOW_FIND_IMAGE_H

#include "window/smallWindow.h"
#include "widget_button.h"
#include "widget_lineEdit.h"
#include "widget_itemlist.h"
#include "widget_roundbutton.h"

#include "global.h"

class Window_find : public SmallWindow
{
    Q_OBJECT

public:

    enum type {
        type_hero,
        type_enemy,
        type_boss,
        type_bullet,
        type_image,
        type_effect,
        type_audio
    };

    explicit Window_find(Database *_db, int _type, int _group, int *_index, QWidget *parent = nullptr);
    explicit Window_find(Database *_db, int _type, int _group, float *_index, QWidget *parent = nullptr);
#define find_create(_db,_type,_group,_index) \
    Window_find *window_find = new Window_find(_db, _type, _group, _index);\
    window_find->setWindowModality(Qt::ApplicationModal);\
    window_find->setAttribute(Qt::WA_DeleteOnClose);\
    window_find->show()

private:
    Database *db;
    int type;
    int group;
    int *index_i;
    float *index_f;
    int index_tp;

    QButtonGroup *buttonBox_type;

    Widget_LineEdit *lineEdit;
    Widget_Button *button_find;
    Widget_Button *button_noone;

    Widget_ItemList *itemList;

public slots:
    void find();
    void getPosition(int _index);
    void getNoone();

signals:
    void OK();

};


#endif // WINDOW_FIND_IMAGE_H
