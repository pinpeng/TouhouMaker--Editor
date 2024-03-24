#include "window_editor_menubar_bullet.h"

Window_editor_menubar_bullet::Window_editor_menubar_bullet(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 900);
    setWindowTitle("编辑子弹");

    db = Global::database();

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(720 - 28, 900 - 96, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(_timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(960 - 20, 900 - 96, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(_timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    QString _text[3] = { "BOSS", "小怪", "主角" };

    select_group = new QButtonGroup(this);
    for(int i = 0; i < 3; i ++) {
        roundButton[i] = new Widget_RoundButton(this);
        roundButton[i]->setText(_text[i]);
        roundButton[i]->setGeometry(48 + 180 * i, 84, 180, 60);
        roundButton[i]->setTimer(_timer);
        select_group->addButton(roundButton[i]);
        connect(roundButton[i], SIGNAL(stateChanged()), this, SLOT(updateList()));
    }

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1200 - 36, 580);

    button_add = new Widget_Button(this);
    button_del = new Widget_Button(this);
    button_add->setGeometry(12, 724, 580, 80);
    button_add->setText("新建");
    button_add->setTimer(_timer);
    button_del->setGeometry(600, 724, 580, 80);
    button_del->setText("删除");
    button_del->setTimer(_timer);

    connect(button_add, SIGNAL(pressed()), this, SLOT(add()));
    connect(button_del, SIGNAL(pressed()), this, SLOT(del()));

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(editBullet(int)));

    roundButton[0]->setChecked(true);
    updateList();
}

void Window_editor_menubar_bullet::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_editor_menubar_bullet::updateList()
{
    QList<itemSTR> tmpList;
    QList<QString> text_list;
    text_list << "ID" << "名称";
    itemList->setHeadTextList(text_list);
    itemList->setHeadWidthList({120, 360});

    int tmp = -1;
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) tmp = i;

    for(auto i = db.bullet[tmp].begin(); i != db.bullet[tmp].end(); i ++) {
        itemSTR tmp_item;
        tmp_item.text.append(QString::number(i.value().__id));
        tmp_item.text.append(i.value().name);
        tmpList.append(tmp_item);
    }
    itemList->setItemList(tmpList);
}

void Window_editor_menubar_bullet::accept()
{
    Global::databaseUpdate(db);
    end();
}


void Window_editor_menubar_bullet::editBullet(int _index)
{
    if(_index == -1) return;
    if(itemList->index() == -1) return;

    editBulletStart(itemList->getItem(_index).text[0].toInt());
}

void Window_editor_menubar_bullet::editBulletStart(int _index)
{
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) {
        window_editor = new Window_editor_menubar_bullet_edit(&db, &db.bullet[i][_index], i);
        connect(window_editor, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor->setWindowModality(Qt::ApplicationModal);
        window_editor->setAttribute(Qt::WA_DeleteOnClose);
        window_editor->show();
    }
}


void Window_editor_menubar_bullet::add()
{
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.bullet_append(i);

    itemList->resetIndex();
    updateList();
}

void Window_editor_menubar_bullet::del()
{
    int index = itemList->index();
    if(index == -1) { Message_Box::play(this, "未选中项目"); return; }

    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.bullet_delete(i, itemList->getItem(index).text[0].toInt());

    itemList->resetIndex();
    updateList();
}



