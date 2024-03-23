#ifndef WINDOW_ASK_H
#define WINDOW_ASK_H

#include "window/smallWindow.h"

#include "widget_button.h"
#include "widget_choosebutton.h"
#include "widget_lineEdit.h"
#include "widget_dragstick.h"
#include "widget_textEdit.h"

#include "window_find.h"

#include "database.h"

class Window_ask : public SmallWindow
{
    Q_OBJECT

public:
    explicit Window_ask(QString _text, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setText(QString _text);

private:
    QString text;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

public slots:
    void accept_slot();

signals:
    void OK();
};


class Window_ask_ex : public SmallWindow
{
    Q_OBJECT

    enum ITEM_TYPE {
        NONE,
        TEXT,
        TEXTLINE_STR,
        TEXTLINE_FLOAT_i,
        TEXTLINE_FLOAT_f,
        TEXTLINE_INT_i,
        TEXTLINE_INT_f,
        DRAG_STICK_i,
        DRAG_STICK_f,
        FIND_BUTTON_i,
        FIND_BUTTON_f,
        CHOOSE_BUTTON_i,
        CHOOSE_BUTTON_f
    };

public:
    explicit Window_ask_ex(QString _title, Database *_db = nullptr, QWidget *parent = nullptr);

#define ask_create(_title) Window_ask_ex *window_ask_ex = new Window_ask_ex(_title); \
    window_ask_ex->setWindowModality(Qt::ApplicationModal); \
    window_ask_ex->setAttribute(Qt::WA_DeleteOnClose); \
    window_ask_ex->show()

#define ask_create_db(_title,_db) Window_ask_ex *window_ask_ex = new Window_ask_ex(_title, _db); \
    window_ask_ex->setWindowModality(Qt::ApplicationModal); \
    window_ask_ex->setAttribute(Qt::WA_DeleteOnClose); \
    window_ask_ex->show()

    void resetSize(int line_now);

    void paintEvent(QPaintEvent *) override;

    void setPageNumber(int _page);
#define ask_set_page_number(_page) \
    window_ask_ex->setPageNumber(_page)
    void setCurrentPage(int _page);
#define ask_set_current_page(_page) \
    window_ask_ex->setCurrentPage(_page)

    void addTextEdit(QString _text, QString *_str);
#define ask_add_textEdit(_text,_str) \
    window_ask_ex->addTextEdit(_text, _str)

    void addLineEdit(QString _text, QString *_str);
    void addLineEdit(QString _text, int *_val, float _min, float _max, bool _isInt);
    void addLineEdit(QString _text, float *_val, float _min, float _max, bool _isInt);
#define ask_add_lineEdit_str(_text,_str) \
    window_ask_ex->addLineEdit(_text, _str)
#define ask_add_lineEdit_float(_text,_val,_min,_max) \
    window_ask_ex->addLineEdit(_text, _val, _min, _max, false)
#define ask_add_lineEdit_int(_text,_val,_min,_max) \
    window_ask_ex->addLineEdit(_text, _val, _min, _max, true)

    void addChooseButton(QString _text, int *_index, QStringList _str_list);
    void addChooseButton(QString _text, float *_index, QStringList _str_list);
#define ask_add_chooseButton(_text,_index,_str_list) \
    window_ask_ex->addChooseButton(_text, _index, _str_list)

    void addDragStick(QString _text, int *_val, float min, float max, QString _val_text, float _mul);
    void addDragStick(QString _text, float *_val, float min, float max, QString _val_text, float _mul);
#define ask_add_dragStick(_text,_val,_min,_max,_val_text,_mul) \
    window_ask_ex->addDragStick(_text, _val, _min, _max, _val_text, _mul)

    void addFindButton(QString _text, int _type, int _group, int *_index);
    void addFindButton(QString _text, int _type, int _group, float *_index);
#define ask_add_findButton(_text,_type,_group,_index) \
    window_ask_ex->addFindButton(_text, _type, _group, _index)

private:
    Database *db;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;

    int page_number = 1;
    int page = 0;

    int typeList [2][16];
    int idList [2][16];
    QString textList[2][16];

    Widget_TextEdit *w_textEdit[16];
    QString *w_textEdit_data_s[16];

    Widget_LineEdit *w_lineEdit[16];
    QString *w_lineEdit_data_s[16];
    int *w_lineEdit_data_i[16];
    float *w_lineEdit_data_f[16];
    float w_lineEdit_data_min[16];
    float w_lineEdit_data_max[16];

    Widget_ChooseButton *w_chooseButton[16];
    int *w_chooseButton_data_i[16];
    float *w_chooseButton_data_f[16];

    Widget_DragStick *w_dragStick[16];
    int *w_dragStick_data_i[16];
    float *w_dragStick_data_f[16];

    Widget_Button *w_findButton[16];
    int *w_findButton_data_i[16];
    float *w_findButton_data_f[16];
    int w_findButton_type[16];
    int w_findButton_group[16];
    int *w_findButton_data_buffer_i[16];
    float *w_findButton_data_buffer_f[16];


public slots:
    void findButtonPressed0_i();
    void findButtonPressed1_i();
    void findButtonPressed2_i();
    void findButtonPressed3_i();
    void findButtonPressed0_f();
    void findButtonPressed1_f();
    void findButtonPressed2_f();
    void findButtonPressed3_f();
    void accept_slot();

signals:
    void OK();
};


#endif // WINDOW_ASK_H
