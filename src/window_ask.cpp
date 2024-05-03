#include "window_ask.h"

#include <QApplication>
#include <QDesktopWidget>

#include "memoryCache/cacheAgent.h"
#include <QApplication>
#include <qt_windows.h>
#include <QDesktopWidget>

Window_ask::Window_ask(QString _text, QWidget *parent) : Window_small(parent)
{
    setFixedSize(800, 240);
    setWindowTitle("提问");

    text = _text;

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(160 - 8, 144, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(400 + 8, 144, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept_slot()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));
}

void Window_ask::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();

    setPenColor_c(c_textMain);
    Draw::setTextDefault();
    Draw::text(rect().center().x(), 100 + 4, text);

    Draw::end();
}

void Window_ask::setText(QString _text)
{
    text = _text;
}

void Window_ask::accept_slot()
{
    emit OK();
    end();
}

Window_ask_ex::Window_ask_ex(QString _title, ProjectData *_db, QWidget *parent) : Window_small(parent)
{
    setFixedSize(800, 160);
    setWindowTitle(_title);

    db = _db;

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(160 - 8, 160 - 96, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(400 + 8, 160 - 96, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept_slot()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    for(int i = 0; i < 2; i ++) {
        for(int j = 0; j < 16; j ++) {
            typeList[i][j] = ITEM_TYPE::NONE;
            idList[i][j] = -1;
            textList[i][j] = "";
        }
    }

    for(int i = 0; i < 16; i ++) {
        w_textEdit[i] = nullptr;
        w_lineEdit[i] = nullptr;
        w_chooseButton[i] = nullptr;
        w_findButton[i] = nullptr;
        w_dragStick[i] = nullptr;
    }
}

void Window_ask_ex::resetSize(int line_now)
{
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(page_number == 1) {
        setFixedSize(800, 160 + 80 * (line_now + 1));
        button_accept->setGeometry(160 - 8, 64 + 80 * (line_now + 1), 240, 80);
        button_cancel->setGeometry(400 + 8, 64 + 80 * (line_now + 1), 240, 80);
    } else {
        if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
        {
            setFixedSize(1560, 160 + 80 * (line_now + 1));
            button_accept->setGeometry(550 - 8, 64 + 80 * (line_now + 1), 240, 80);
            button_cancel->setGeometry(770 + 8, 64 + 80 * (line_now + 1), 240, 80);
        }
        else
        {
            //缩小1.3倍
            setFixedSize(1200, 160 + 80 * (line_now + 1));
            button_accept->setGeometry(423 - 8, 64 + 80 * (line_now + 1), 160, 80);
            button_cancel->setGeometry(593 + 8, 64 + 80 * (line_now + 1), 160, 80);
        }
    }
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

void Window_ask_ex::paintEvent(QPaintEvent *)
{
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        Draw::smallWindow(this, this);

        Draw::begin(this);
        Draw::setAntialising();

        setPenColor_c(c_textMain);
        Draw::setTextDefault();

        for(int i = 0; i < page_number; i ++) {
            int line_now = 0;
            for(int j = 0; j < 16; j ++) {
                if(idList[i][j] == -1) break;
                switch (typeList[i][j]) {
                case ITEM_TYPE::TEXT:
                    //Draw::text(rect().left() + 32 + 760 * i, 104 + line_now * 80, textList[i][j], Qt::AlignLeft | Qt::AlignVCenter);
                    line_now += 3;
                    break;

                case ITEM_TYPE::TEXTLINE_STR:
                case ITEM_TYPE::TEXTLINE_INT_i:
                case ITEM_TYPE::TEXTLINE_INT_f:
                case ITEM_TYPE::TEXTLINE_FLOAT_i:
                case ITEM_TYPE::TEXTLINE_FLOAT_f:
                case ITEM_TYPE::CHOOSE_BUTTON_i:
                case ITEM_TYPE::CHOOSE_BUTTON_f:
                case ITEM_TYPE::DRAG_STICK_i:
                case ITEM_TYPE::DRAG_STICK_f:
                    //QRect rect_scr = QApplication::desktop()->screenGeometry();
                    //if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
                    //{
                    Draw::text(rect().left() + 32 + 760 * i, 104 + line_now * 80, textList[i][j], Qt::AlignLeft | Qt::AlignVCenter);
                    line_now ++;
                    break;

                case ITEM_TYPE::FIND_BUTTON_i:
                case ITEM_TYPE::FIND_BUTTON_f: {
                    int _id = idList[i][j];
                    bool type = typeList[i][j] == ITEM_TYPE::FIND_BUTTON_i;
                    QString _str = "<未选择>";
                    int _id_item;
                    if(type) _id_item = *w_findButton_data_buffer_i[_id];
                    else _id_item = *w_findButton_data_buffer_f[_id];

                    switch(w_findButton_type[_id]) {

                    case Window_find::type_hero: {
                        if(db->hero.find(_id_item) != db->hero.end()) {
                            _str = "<" + db->getText(db->hero[_id_item].name, 0) + ">";
                        }
                    } break;

                    case Window_find::type_enemy: {
                        if(db->enemy.find(_id_item) != db->enemy.end()) {
                            _str = "<" + db->enemy[_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_boss: {
                        if(db->boss.find(_id_item) != db->boss.end()) {
                            _str = "<" + db->getText(db->boss[_id_item].name, 0) + ">";
                        }
                    } break;

                    case Window_find::type_bullet: {
                        if(db->bullet[w_findButton_group[_id]].find(_id_item) != db->bullet[w_findButton_group[_id]].end()) {
                            _str = "<" + db->bullet[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_image: {
                        if(db->image[w_findButton_group[_id]].find(_id_item) != db->image[w_findButton_group[_id]].end()) {
                            _str = "<" + db->image[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_effect: {
                        if(db->effect[w_findButton_group[_id]].find(_id_item) != db->effect[w_findButton_group[_id]].end()) {
                            _str = "<" + db->effect[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_audio: {
                        if(db->audio[w_findButton_group[_id]].find(_id_item) != db->audio[w_findButton_group[_id]].end()) {
                            _str = "<" + db->audio[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    default:
                        break;
                    }

                    Draw::text(rect().left() + 32 + 760 * i, 104 + line_now * 80, textList[i][j] + _str, Qt::AlignLeft | Qt::AlignVCenter);
                    line_now ++;
                } break;

                case ITEM_TYPE::NONE:
                default:
                    break;
                }
            }
        }

        Draw::end();
    }
    else
    {
        Draw::smallWindow(this, this);

        Draw::begin(this);
        Draw::setAntialising();

        setPenColor_c(c_textMain);
        Draw::setTextDefault();

        for(int i = 0; i < page_number; i ++) {
            int line_now = 0;
            for(int j = 0; j < 16; j ++) {
                if(idList[i][j] == -1) break;
                switch (typeList[i][j]) {
                case ITEM_TYPE::TEXT:
                    //Draw::text(rect().left() + 32 + 760 * i, 104 + line_now * 80, textList[i][j], Qt::AlignLeft | Qt::AlignVCenter);
                    line_now += 3;
                    break;

                case ITEM_TYPE::TEXTLINE_STR:
                case ITEM_TYPE::TEXTLINE_INT_i:
                case ITEM_TYPE::TEXTLINE_INT_f:
                case ITEM_TYPE::TEXTLINE_FLOAT_i:
                case ITEM_TYPE::TEXTLINE_FLOAT_f:
                case ITEM_TYPE::CHOOSE_BUTTON_i:
                case ITEM_TYPE::CHOOSE_BUTTON_f:
                case ITEM_TYPE::DRAG_STICK_i:
                case ITEM_TYPE::DRAG_STICK_f:
                    //QRect rect_scr = QApplication::desktop()->screenGeometry();
                    //if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
                    //{
                    Draw::text(rect().left() + 32 + 560 * i, 104 + line_now * 80, textList[i][j], Qt::AlignLeft | Qt::AlignVCenter);
                    line_now ++;
                    break;

                case ITEM_TYPE::FIND_BUTTON_i:
                case ITEM_TYPE::FIND_BUTTON_f: {
                    int _id = idList[i][j];
                    bool type = typeList[i][j] == ITEM_TYPE::FIND_BUTTON_i;
                    QString _str = "<未选择>";
                    int _id_item;
                    if(type) _id_item = *w_findButton_data_buffer_i[_id];
                    else _id_item = *w_findButton_data_buffer_f[_id];

                    switch(w_findButton_type[_id]) {

                    case Window_find::type_hero: {
                        if(db->hero.find(_id_item) != db->hero.end()) {
                            _str = "<" + db->getText(db->hero[_id_item].name, 0) + ">";
                        }
                    } break;

                    case Window_find::type_enemy: {
                        if(db->enemy.find(_id_item) != db->enemy.end()) {
                            _str = "<" + db->enemy[_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_boss: {
                        if(db->boss.find(_id_item) != db->boss.end()) {
                            _str = "<" + db->getText(db->boss[_id_item].name, 0) + ">";
                        }
                    } break;

                    case Window_find::type_bullet: {
                        if(db->bullet[w_findButton_group[_id]].find(_id_item) != db->bullet[w_findButton_group[_id]].end()) {
                            _str = "<" + db->bullet[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_image: {
                        if(db->image[w_findButton_group[_id]].find(_id_item) != db->image[w_findButton_group[_id]].end()) {
                            _str = "<" + db->image[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_effect: {
                        if(db->effect[w_findButton_group[_id]].find(_id_item) != db->effect[w_findButton_group[_id]].end()) {
                            _str = "<" + db->effect[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    case Window_find::type_audio: {
                        if(db->audio[w_findButton_group[_id]].find(_id_item) != db->audio[w_findButton_group[_id]].end()) {
                            _str = "<" + db->audio[w_findButton_group[_id]][_id_item].name + ">";
                        }
                    } break;

                    default:
                        break;
                    }

                    Draw::text(rect().left() + 32 + 760 * i, 104 + line_now * 80, textList[i][j] + _str, Qt::AlignLeft | Qt::AlignVCenter);
                    line_now ++;
                } break;

                case ITEM_TYPE::NONE:
                default:
                    break;
                }
            }
        }

        Draw::end();

    }

}

void Window_ask_ex::setPageNumber(int _page)
{
    page_number = _page;
}

void Window_ask_ex::setCurrentPage(int _page)
{
    page = _page;
}

void Window_ask_ex::addTextEdit(QString _text, QString *_str)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_textEdit[id] == nullptr) break;

    typeList[page][i] = ITEM_TYPE::TEXT;
    idList[page][i] = id;
//    textList[page][i] = _text;
    w_textEdit[id] = new Widget_TextEdit(this);

    w_textEdit[id]->show();
    Draw::setTextSize(16);
    w_textEdit[id]->setFont(Draw::font);
    w_textEdit[id]->setText(*_str);
    w_textEdit[id]->setBackgroundText(_text);
    w_textEdit_data_s[id] = _str;
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_textEdit[id]->setGeometry(40 + 760 * page, 64 + 80 * (line_now), 720, 80 + 160);
    }
    else
    {
        w_textEdit[id]->setGeometry(40 + 584 * page, 64 + 80 * (line_now), 553, 80 + 160);
    }

    line_now += 2;

    resetSize(line_now);
}

void Window_ask_ex::addLineEdit(QString _text, QString *_str)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_lineEdit[id] == nullptr) break;

    typeList[page][i] = ITEM_TYPE::TEXTLINE_STR;
    idList[page][i] = id;
    textList[page][i] = _text;
    w_lineEdit[id] = new Widget_LineEdit(this);

    w_lineEdit[id]->show();
    w_lineEdit[id]->setText(*_str);
    w_lineEdit_data_s[id] = _str;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_lineEdit[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_lineEdit[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addLineEdit(QString _text, int *_val, float _min, float _max, bool _isInt)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_lineEdit[id] == nullptr) break;
    if(_isInt) typeList[page][i] = ITEM_TYPE::TEXTLINE_INT_i;
    else typeList[page][i] = ITEM_TYPE::TEXTLINE_FLOAT_i;
    idList[page][i] = id;
    textList[page][i] = _text;
    w_lineEdit[id] = new Widget_LineEdit(this);

    w_lineEdit[id]->show();
    w_lineEdit[id]->setText(QString::number(*_val));
    w_lineEdit_data_i[id] = _val;

    w_lineEdit_data_min[id] = _min;
    w_lineEdit_data_max[id] = _max;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_lineEdit[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_lineEdit[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addLineEdit(QString _text, float *_val, float _min, float _max, bool _isInt)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_lineEdit[id] == nullptr) break;
    if(_isInt) typeList[page][i] = ITEM_TYPE::TEXTLINE_INT_f;
    else typeList[page][i] = ITEM_TYPE::TEXTLINE_FLOAT_f;
    idList[page][i] = id;
    textList[page][i] = _text;
    w_lineEdit[id] = new Widget_LineEdit(this);

    w_lineEdit[id]->show();
    w_lineEdit[id]->setText(QString::number(*_val));
    w_lineEdit_data_f[id] = _val;

    w_lineEdit_data_min[id] = _min;
    w_lineEdit_data_max[id] = _max;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_lineEdit[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_lineEdit[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addChooseButton(QString _text, int *_index, QStringList _str_list)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_chooseButton[id] == nullptr) break;
    typeList[page][i] = ITEM_TYPE::CHOOSE_BUTTON_i;
    idList[page][i] = id;
    textList[page][i] = _text;
    w_chooseButton[id] = new Widget_ChooseButton(this);

    w_chooseButton[id]->show();
    w_chooseButton[id]->setTimer(timer);
    w_chooseButton[id]->addTextList(_str_list);
    w_chooseButton[id]->setIndex(*_index);
    w_chooseButton_data_i[id] = _index;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_chooseButton[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_chooseButton[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addChooseButton(QString _text, float *_index, QStringList _str_list)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_chooseButton[id] == nullptr) break;
    typeList[page][i] = ITEM_TYPE::CHOOSE_BUTTON_f;
    idList[page][i] = id;
    textList[page][i] = _text;
    w_chooseButton[id] = new Widget_ChooseButton(this);

    w_chooseButton[id]->show();
    w_chooseButton[id]->setTimer(timer);
    w_chooseButton[id]->addTextList(_str_list);
    w_chooseButton[id]->setIndex(*_index);
    w_chooseButton_data_f[id] = _index;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_chooseButton[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_chooseButton[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addDragStick(QString _text, int *_val, float min, float max, QString _val_text, float _mul)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_dragStick[id] == nullptr) break;
    typeList[page][i] = ITEM_TYPE::DRAG_STICK_i;
    idList[page][i] = id;
    textList[page][i] = _text;

    w_dragStick[id] = new Widget_DragStick(this);
    w_dragStick[id]->show();
    w_dragStick[id]->setTimer(timer);
    w_dragStick[id]->setRange(min, max);
    w_dragStick[id]->setValue(*_val);
    w_dragStick[id]->setText(_val_text);
    w_dragStick[id]->setShowMul(_mul);
    w_dragStick_data_i[id] = _val;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_dragStick[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_dragStick[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addDragStick(QString _text, float *_val, float min, float max, QString _val_text, float _mul)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_dragStick[id] == nullptr) break;
    typeList[page][i] = ITEM_TYPE::DRAG_STICK_f;
    idList[page][i] = id;
    textList[page][i] = _text;

    w_dragStick[id] = new Widget_DragStick(this);
    w_dragStick[id]->show();
    w_dragStick[id]->setTimer(timer);
    w_dragStick[id]->setRange(min, max);
    w_dragStick[id]->setValue(*_val);
    w_dragStick[id]->setText(_val_text);
    w_dragStick[id]->setShowMul(_mul);
    w_dragStick_data_f[id] = _val;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_dragStick[id]->setGeometry(280 + 760 * page, 64 + 80 * line_now, 480, 80);
    }
    else
    {
        w_dragStick[id]->setGeometry(280 + 560 * page, 64 + 80 * line_now, 300, 80);
    }

    resetSize(line_now);
}

void Window_ask_ex::addFindButton(QString _text, int _type, int _group, int *_index)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_findButton[id] == nullptr) break;
    typeList[page][i] = ITEM_TYPE::FIND_BUTTON_i;
    idList[page][i] = id;
    textList[page][i] = _text;

    w_findButton[id] = new Widget_Button(this);
    w_findButton[id]->show();
    w_findButton[id]->setTimer(timer);
    w_findButton[id]->setText("更改");
    w_findButton_type[id] = _type;
    w_findButton_group[id] = _group;
    w_findButton_data_i[id] = _index;
    w_findButton_data_buffer_i[id] = new int;
    *w_findButton_data_buffer_i[id] = *_index;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_findButton[id]->setGeometry(480 + 760 * page, 64 + 80 * line_now, 280, 80);
    }
    else
    {
        w_findButton[id]->setGeometry(480 + 560 * page, 64 + 80 * line_now, 215, 80);
    }

    if(id == 0) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed0_i()));
    if(id == 1) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed1_i()));
    if(id == 2) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed2_i()));
    if(id == 3) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed3_i()));

    resetSize(line_now);
}

void Window_ask_ex::addFindButton(QString _text, int _type, int _group, float *_index)
{
    int i, id, line_now = 0;
    for(i = 0; i < 16; i ++) {
        if(idList[page][i] == -1) break;
        if(typeList[page][i] == ITEM_TYPE::TEXT) {
            line_now += 3;
        } else line_now += 1;
    }
    for(id = 0; id < 16; id ++) if(w_findButton[id] == nullptr) break;
    typeList[page][i] = ITEM_TYPE::FIND_BUTTON_f;
    idList[page][i] = id;
    textList[page][i] = _text;

    w_findButton[id] = new Widget_Button(this);
    w_findButton[id]->show();
    w_findButton[id]->setTimer(timer);
    w_findButton[id]->setText("更改");
    w_findButton_type[id] = _type;
    w_findButton_group[id] = _group;
    w_findButton_data_f[id] = _index;
    w_findButton_data_buffer_f[id] = new float;
    *w_findButton_data_buffer_f[id] = *_index;

    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        w_findButton[id]->setGeometry(480 + 760 * page, 64 + 80 * line_now, 280, 80);
    }
    else
    {
        w_findButton[id]->setGeometry(480 + 560 * page, 64 + 80 * line_now, 215, 80);
    }

    if(id == 0) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed0_f()));
    if(id == 1) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed1_f()));
    if(id == 2) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed2_f()));
    if(id == 3) connect(w_findButton[id], SIGNAL(pressed()), this, SLOT(findButtonPressed3_f()));

    resetSize(line_now);
}

void Window_ask_ex::findButtonPressed0_i()
{
    int tmp = 0;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_i[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed1_i()
{
    int tmp = 1;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_i[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed2_i()
{
    int tmp = 2;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_i[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed3_i()
{
    int tmp = 3;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_i[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed0_f()
{
    int tmp = 0;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_f[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed1_f()
{
    int tmp = 1;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_f[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed2_f()
{
    int tmp = 2;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_f[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::findButtonPressed3_f()
{
    int tmp = 3;
    Window_find *window_find;
    window_find = new Window_find(db, w_findButton_type[tmp], w_findButton_group[tmp], w_findButton_data_buffer_f[tmp]);
    window_find->setWindowModality(Qt::ApplicationModal);
    window_find->setAttribute(Qt::WA_DeleteOnClose);
    window_find->show();
    connect(window_find, SIGNAL(OK()), this, SLOT(repaint()));
}

void Window_ask_ex::accept_slot()
{

    for(int i = 0; i < page_number; i ++) {
        for(int j = 0; j < 16; j ++) {
            if(idList[i][j] == -1) break;
            int id = idList[i][j];
            switch (typeList[i][j]) {
            case ITEM_TYPE::TEXT:
                *w_textEdit_data_s[id] = w_textEdit[id]->text();
                break;
            case ITEM_TYPE::TEXTLINE_STR:
                *w_lineEdit_data_s[id] = w_lineEdit[id]->text();
                break;
            case ITEM_TYPE::TEXTLINE_INT_i:
                *w_lineEdit_data_i[id] = int(qBound(w_lineEdit_data_min[id], w_lineEdit[id]->text().toFloat(), w_lineEdit_data_max[id]));
                break;
            case ITEM_TYPE::TEXTLINE_INT_f:
                *w_lineEdit_data_f[id] = int(qBound(w_lineEdit_data_min[id], w_lineEdit[id]->text().toFloat(), w_lineEdit_data_max[id]));
                break;
            case ITEM_TYPE::TEXTLINE_FLOAT_i:
                *w_lineEdit_data_i[id] = qBound(w_lineEdit_data_min[id], w_lineEdit[id]->text().toFloat(), w_lineEdit_data_max[id]);
                break;
            case ITEM_TYPE::TEXTLINE_FLOAT_f:
                *w_lineEdit_data_f[id] = qBound(w_lineEdit_data_min[id], w_lineEdit[id]->text().toFloat(), w_lineEdit_data_max[id]);
                break;
            case ITEM_TYPE::CHOOSE_BUTTON_i:
                *w_chooseButton_data_i[id] = w_chooseButton[id]->getIndex();
                break;
            case ITEM_TYPE::CHOOSE_BUTTON_f:
                *w_chooseButton_data_f[id] = float(w_chooseButton[id]->getIndex());
                break;
            case ITEM_TYPE::DRAG_STICK_i:
                *w_dragStick_data_i[id] = int(w_dragStick[id]->getValue());
                break;
            case ITEM_TYPE::DRAG_STICK_f:
                *w_dragStick_data_f[id] = w_dragStick[id]->getValue();
                break;
            case ITEM_TYPE::FIND_BUTTON_i:
                *w_findButton_data_i[id] = *w_findButton_data_buffer_i[id];
                delete w_findButton_data_buffer_i[id];
                break;
            case ITEM_TYPE::FIND_BUTTON_f:
                *w_findButton_data_f[id] = *w_findButton_data_buffer_f[id];
                delete w_findButton_data_buffer_f[id];
                break;
            case ITEM_TYPE::NONE:
            default:
                break;
            }
        }
    }

    emit OK();
    end();

}
