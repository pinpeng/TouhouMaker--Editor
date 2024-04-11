#include "window_editor_menubar_effect.h"

Window_editor_menubar_effect::Window_editor_menubar_effect(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 900);
    setWindowTitle("编辑特效");

    db = CacheAgent::getInstance().database();

    button_accept = new GradientButton(this);
    button_accept->setGeometry(720 - 28, 900 - 96, 240, 80);
    button_accept->setText("确定");
    // button_accept->setTimer(_timer);

    button_cancel = new GradientButton(this);
    button_cancel->setGeometry(960 - 20, 900 - 96, 240, 80);
    button_cancel->setText("取消");
    // button_cancel->setTimer(_timer);

    QString _text[3] = { "子弹特效", "场景特效", "角色特效" };

    select_group = new QButtonGroup(this);
    for(int i = 0; i < 3; i ++) {
        roundButton[i] = new RoundButton(this);
        roundButton[i]->setText(_text[i]);
        roundButton[i]->setGeometry(48 + 180 * i, 84, 180, 60);
        select_group->addButton(roundButton[i]);
        connect(roundButton[i], SIGNAL(stateChanged()), this, SLOT(updateList()));
    }

    itemList = new ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1200 - 36, 580);


    button_add = new GradientButton(this);
    button_del = new GradientButton(this);
    button_add->setGeometry(12, 724, 580, 80);
    button_add->setText("新建");
    // button_add->setTimer(_timer);
    button_del->setGeometry(600, 724, 580, 80);
    button_del->setText("删除");
    // button_del->setTimer(_timer);

    connect(button_add, SIGNAL(pressed()), this, SLOT(add()));
    connect(button_del, SIGNAL(pressed()), this, SLOT(del()));

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(editHero(int)));

    roundButton[0]->setChecked(true);
    updateList();
}

void Window_editor_menubar_effect::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_editor_menubar_effect::updateList()
{
    QList<itemSTR> tmpList;
    QList<QString> text_list;
    text_list << "ID" << "名称";
    itemList->setHeadTextList(text_list);
    itemList->setHeadWidthList({120, 360});

    int tmp = -1;
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) tmp = i;

    for(auto i = db.effect[tmp].begin(); i != db.effect[tmp].end(); i ++) {
        itemSTR tmp_item;
        tmp_item.text.append(QString::number(i.value().__id));
        tmp_item.text.append(i.value().name);
        tmpList.append(tmp_item);

    }

    itemList->setItemList(tmpList);
}

void Window_editor_menubar_effect::accept()
{
    CacheAgent::getInstance().databaseUpdate(db);
    end();
}


void Window_editor_menubar_effect::editHero(int _index)
{
    if(_index == -1) return;
    if(itemList->index() == -1) return;

    editHeroStart(itemList->getItem(_index).text[0].toInt());
}

void Window_editor_menubar_effect::editHeroStart(int _index)
{
    if(roundButton[0]->isChecked()) {
        window_editor0 = new Window_editor_menubar_effect_edit0(&db, &db.effect[0][_index]);
        connect(window_editor0, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor0->setWindowModality(Qt::ApplicationModal);
        window_editor0->setAttribute(Qt::WA_DeleteOnClose);
        window_editor0->show();
    }
    if(roundButton[1]->isChecked()) {
        window_editor1 = new Window_editor_menubar_effect_edit1(&db, &db.effect[1][_index]);
        connect(window_editor1, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor1->setWindowModality(Qt::ApplicationModal);
        window_editor1->setAttribute(Qt::WA_DeleteOnClose);
        window_editor1->show();
    }
    if(roundButton[2]->isChecked()) {
        window_editor2 = new Window_editor_menubar_effect_edit2(&db, &db.effect[2][_index]);
        connect(window_editor2, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor2->setWindowModality(Qt::ApplicationModal);
        window_editor2->setAttribute(Qt::WA_DeleteOnClose);
        window_editor2->show();
    }
}

void Window_editor_menubar_effect::add()
{
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.effect_append(i);

    itemList->resetIndex();
    updateList();
}

void Window_editor_menubar_effect::del()
{
    int index = itemList->index();
    if(index == -1) { TransparentDialog::play(this, "未选中项目"); return; }
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.effect_delete(i, itemList->getItem(index).text[0].toInt());

    itemList->resetIndex();
    updateList();
}



