#include "window_find.h"

Window_find::Window_find(ProjectData *_db, int _type, int _group, int *_index, QWidget *parent) : Window_small(parent)
{
    setFixedSize(960, 900);

    db = _db;
    type = _type;
    group = _group;
    index_tp = 0;
    index_i = _index;
    if(type == type_hero) {
        setWindowTitle("搜索主角");
    } else if(type == type_enemy) {
        setWindowTitle("搜索小怪");
    } else if(type == type_boss) {
        setWindowTitle("搜索BOSS");
    } else if(type == type_bullet) {
        setWindowTitle("搜索子弹");
    } else if(type == type_image) {
        setWindowTitle("搜索图像");
    } else if(type == type_effect) {
        setWindowTitle("搜索特效");
    } else if(type == type_audio) {
        setWindowTitle("搜索音频");
    }

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32, 64, 720 - 64, 80);
    lineEdit->setText("");

    button_find = new Widget_Button(this);
    button_find->setGeometry(720 - 32, 64, 240, 80);
    button_find->setText("搜索");
    button_find->setTimer(timer);

    button_noone = new Widget_Button(this);
    button_noone->setGeometry(32, 804, 960 - 64, 80);
    button_noone->setText("取消选择");
    button_noone->setTimer(timer);

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1000 - 76, 660);

    connect(button_find, SIGNAL(pressed()), this, SLOT(find()));
    connect(button_noone, SIGNAL(pressed()), this, SLOT(getNoone()));
    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(getPosition(int)));

    find();
}

Window_find::Window_find(ProjectData *_db, int _type, int _group, float *_index, QWidget *parent) : Window_small(parent)
{
    setFixedSize(960, 900);

    db = _db;
    type = _type;
    group = _group;
    index_tp = 1;
    index_f = _index;
    if(type == type_hero) {
        setWindowTitle("搜索主角");
    } else if(type == type_enemy) {
        setWindowTitle("搜索小怪");
    } else if(type == type_boss) {
        setWindowTitle("搜索BOSS");
    } else if(type == type_bullet) {
        setWindowTitle("搜索子弹");
    } else if(type == type_image) {
        setWindowTitle("搜索图像");
    } else if(type == type_effect) {
        setWindowTitle("搜索特效");
    } else if(type == type_audio) {
        setWindowTitle("搜索音频");
    }

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32, 64, 720 - 64, 80);
    lineEdit->setText("");

    button_find = new Widget_Button(this);
    button_find->setGeometry(720 - 32, 64, 240, 80);
    button_find->setText("搜索");
    button_find->setTimer(timer);

    button_noone = new Widget_Button(this);
    button_noone->setGeometry(32, 804, 960 - 64, 80);
    button_noone->setText("取消选择");
    button_noone->setTimer(timer);

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1000 - 76, 660);

    connect(button_find, SIGNAL(pressed()), this, SLOT(find()));
    connect(button_noone, SIGNAL(pressed()), this, SLOT(getNoone()));
    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(getPosition(int)));

    find();
}

void Window_find::find()
{
    QList<itemSTR> tmpList;
    QList<QString> text_list;
    text_list << "ID" << "名称";
    itemList->setHeadTextList(text_list);
    itemList->setHeadWidthList({120, 540});

    QString _text = lineEdit->text();

    if(type == type_hero) {
        for(auto i = db->hero.begin(); i != db->hero.end(); i ++) {
            if(db->getText(i.value().name, 0).indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(db->getText(i.value().name, 0));
            tmpList.append(tmp_item);
        }
    } else if(type == type_enemy) {
        for(auto i = db->enemy.begin(); i != db->enemy.end(); i ++) {
            if(i.value().name.indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(i.value().name);
            tmpList.append(tmp_item);
        }
    } else if(type == type_boss) {
        for(auto i = db->boss.begin(); i != db->boss.end(); i ++) {
            if(db->getText(i.value().name, 0).indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(db->getText(i.value().name, 0));
            tmpList.append(tmp_item);
        }
    } else if(type == type_bullet) {
        for(auto i = db->bullet[group].begin(); i != db->bullet[group].end(); i ++) {
            if(i.value().name.indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(i.value().name);
            tmpList.append(tmp_item);
        }
    } else if(type == type_image) {
        for(auto i = db->image[group].begin(); i != db->image[group].end(); i ++) {
            if(i.value().name.indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(i.value().name);
            tmpList.append(tmp_item);
        }
    } else if(type == type_effect) {
        for(auto i = db->effect[group].begin(); i != db->effect[group].end(); i ++) {
            if(i.value().name.indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(i.value().name);
            tmpList.append(tmp_item);
        }
    } else if(type == type_audio) {
        for(auto i = db->audio[group].begin(); i != db->audio[group].end(); i ++) {
            if(i.value().name.indexOf(_text) == -1) continue;
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(i.value().name);
            tmpList.append(tmp_item);
        }
    }

    itemList->setItemList(tmpList);

    Message_Box::play(this, "找到" + QString::number(tmpList.size()) + "项");
}

void Window_find::getPosition(int _index)
{
    int tmp = itemList->getItem(_index).text[0].toInt();
    if(index_tp == 0) *index_i = tmp;
    if(index_tp == 1) *index_f = tmp;
    emit OK();
    end();
}

void Window_find::getNoone()
{
    if(index_tp == 0) *index_i = -1;
    if(index_tp == 1) *index_f = -1;
    emit OK();
    end();
}



