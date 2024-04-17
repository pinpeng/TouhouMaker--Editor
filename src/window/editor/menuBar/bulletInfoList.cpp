#include "window/editor/menuBar/BulletInfoList.h"

static int BOSS_GROUP = 1;
static int ENEMY_GROUP = 2;
static int HERO_GROUP = 3;

BulletInfoList::BulletInfoList(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 900);
    setWindowTitle("编辑子弹");

    db = CacheAgent::getInstance().database();

    _acceptbutton = new GradientButton("确定",QRect(720 - 28, 900 - 96, 240, 80),this);

    _cancelbutton = new GradientButton("取消",QRect(960 - 20, 900 - 96, 240, 80),this);

    connect(_acceptbutton, SIGNAL(pressed()), this, SLOT(accept()));
    connect(_cancelbutton, SIGNAL(pressed()), this, SLOT(end()));

    QString _text[3] = { "BOSS", "小怪", "主角" };

    _bulletselectgroup = new QButtonGroup(this);
    for(int i = 0; i < 3; i ++) {
        roundButton[i] = new RoundButton(this);
        roundButton[i]->setText(_text[i]);
        roundButton[i]->setGeometry(48 + 180 * i, 84, 180, 60);
        _bulletselectgroup->addButton(roundButton[i]);
        // TODO... 后续绑定到group上面
        connect(roundButton[i], SIGNAL(stateChanged()), this, SLOT(updateList()));
    }

    itemList = new ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1200 - 36, 580);

    _addbutton = new GradientButton(this);
    _delbutton = new GradientButton(this);
    _addbutton->setGeometry(12, 724, 580, 80);
    _addbutton->setText("新建");

    _delbutton->setGeometry(600, 724, 580, 80);
    _delbutton->setText("删除");


    connect(_addbutton, SIGNAL(pressed()), this, SLOT(add()));
    connect(_delbutton, SIGNAL(pressed()), this, SLOT(del()));

    connect(_acceptbutton, SIGNAL(pressed()), this, SLOT(accept()));
    connect(_cancelbutton, SIGNAL(pressed()), this, SLOT(end()));

    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(editBullet(int)));

    roundButton[0]->setChecked(true);
    updateList();
}

void BulletInfoList::updateList()
{
    QList<itemSTR> tmpList;
    // QList<QString> text_list;
    // text_list << "ID" << "名称";
    itemList->setHeadTextList({"ID","名称"});
    itemList->setHeadWidthList({120, 360});

    // int tmp = -1;
    for(int i = 0; i < 3; i ++){
        if(roundButton[i]->isChecked()){
            _curListGroup = i;
        }
    }

    for(auto i = db.bullet[_curListGroup].begin(); i != db.bullet[_curListGroup].end(); ++i) {
        itemSTR tmp_item;
        tmp_item.text.append(QString::number(i.value().__id));
        tmp_item.text.append(i.value().name);
        tmpList.append(tmp_item);
    }
    itemList->setItemList(tmpList);
}

void BulletInfoList::accept()
{
    CacheAgent::getInstance().databaseUpdate(db);
    end();
}


void BulletInfoList::editBullet(int index)
{
    if(index == -1) return;
    if(itemList->index() == -1) return;

    editBulletStart(itemList->getItem(index).text[0].toInt());
}

void BulletInfoList::editBulletStart(int index)
{
    // for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) {
    window_editor = new BulletEditor(&db, &db.bullet[_curListGroup][index], _curListGroup);
    connect(window_editor, SIGNAL(closed()), this, SLOT(updateList()));
    window_editor->setWindowModality(Qt::ApplicationModal);
    window_editor->setAttribute(Qt::WA_DeleteOnClose);
    window_editor->show();
    // }
}


void BulletInfoList::add()
{
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.bullet_append(i);

    itemList->resetIndex();
    updateList();
}

void BulletInfoList::del()
{
    int index = itemList->index();
    if(index == -1) { TransparentDialog::play(this, "未选中项目"); return; }

    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.bullet_delete(i, itemList->getItem(index).text[0].toInt());

    itemList->resetIndex();
    updateList();
}



