#include "window/editor/menuBar/characterEditor.h"

CharacterEditor::CharacterEditor(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 900);
    setWindowTitle("编辑角色");

    db = CacheAgent::getInstance().database();

    _acceptButton = new GradientButton("确定",QRect(720 - 28, 900 - 96, 240, 80),this);

    _cancelButton = new GradientButton("取消",QRect(960 - 20, 900 - 96, 240, 80),this);

    QString _text[3] = { "主角", "小怪", "BOSS" };

    _characterGroup = new QButtonGroup(this);
    for(int i = 0; i < 3; i ++) {
        roundButton[i] = new RoundButton(this);
        roundButton[i]->setText(_text[i]);
        roundButton[i]->setGeometry(48 + 180 * i, 84, 180, 60);
        _characterGroup->addButton(roundButton[i]);
        // TODO... 后续修改connect到ButtonGroup
        connect(roundButton[i], SIGNAL(stateChanged()), this, SLOT(updateList()));
    }

    // 语言切换按钮，目前就当不存在吧
    chooseButton = new ChooseButton(this);
    chooseButton->addTextList(db.info.language);
    chooseButton->setGeometry(816, 64, 400 - 36, 80);
    connect(chooseButton, SIGNAL(indexChanged(int)), this, SLOT(updateList()));

    _itemList = new ItemList(this);
    _itemList->setGeometry(16, 64 + 80, 1200 - 36, 580);


    _addButton = new GradientButton("新建",QRect(12, 724, 580, 80),this);
    _delButton = new GradientButton("删除",QRect(600, 724, 580, 80),this);

    connect(_acceptButton, SIGNAL(pressed()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(pressed()), this, SLOT(end()));

    connect(_addButton, SIGNAL(pressed()), this, SLOT(add()));
    connect(_delButton, SIGNAL(pressed()), this, SLOT(del()));

    connect(_itemList, SIGNAL(doubleClicked(int)), this, SLOT(editHero(int)));

    roundButton[0]->setChecked(true);
    updateList();
}

void CharacterEditor::updateList()
{
    QList<itemSTR> tmpList;
    // QList<QString> headTextList;
    // headTextList << "ID" << "名称";
    _itemList->setHeadTextList({"ID","名称"});
    _itemList->setHeadWidthList({120, 360});

    if(roundButton[0]->isChecked()) {
        for(auto i = db.hero.begin(); i != db.hero.end(); i ++) {
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(db.getText(i.value().name, chooseButton->getIndex()));
            tmpList.append(tmp_item);
        }
    }
    if(roundButton[1]->isChecked()) {
        for(auto i = db.enemy.begin(); i != db.enemy.end(); i ++) {
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(i.value().name);
            tmpList.append(tmp_item);
        }
    }
    if(roundButton[2]->isChecked()) {
        for(auto i = db.boss.begin(); i != db.boss.end(); i ++) {
            itemSTR tmp_item;
            tmp_item.text.append(QString::number(i.value().__id));
            tmp_item.text.append(db.getText(i.value().name, chooseButton->getIndex()));
            tmpList.append(tmp_item);
        }
    }

    _itemList->setItemList(tmpList);
}

void CharacterEditor::accept()
{
    CacheAgent::getInstance().databaseUpdate(db);
    end();
}


void CharacterEditor::editHero(int _index)
{
    if(_index == -1) return;
    if(_itemList->index() == -1) return;

    editHeroStart(_itemList->getItem(_index).text[0].toInt());
}

void CharacterEditor::editHeroStart(int _index)
{
    if(roundButton[0]->isChecked()) {
        TransparentDialog::play("功能开发中");
        /*
        window_editor0 = new Window_editor_menubar_hero_edit0(&db, &db.hero[_index]);
        connect(window_editor0, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor0->setWindowModality(Qt::ApplicationModal);
        window_editor0->setAttribute(Qt::WA_DeleteOnClose);
        window_editor0->show();
        */
    }
    if(roundButton[1]->isChecked()) {
        window_editor1 = new Window_editor_menubar_hero_edit1(&db, &db.enemy[_index]);
        connect(window_editor1, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor1->setWindowModality(Qt::ApplicationModal);
        window_editor1->setAttribute(Qt::WA_DeleteOnClose);
        window_editor1->show();
    }
    if(roundButton[2]->isChecked()) {
        window_editor2 = new Window_editor_menubar_hero_edit2(&db, &db.boss[_index]);
        connect(window_editor2, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor2->setWindowModality(Qt::ApplicationModal);
        window_editor2->setAttribute(Qt::WA_DeleteOnClose);
        window_editor2->show();
    }
}

void CharacterEditor::add()
{
    if(roundButton[0]->isChecked()) db.hero_append();
    if(roundButton[1]->isChecked()) db.enemy_append();
    if(roundButton[2]->isChecked()) db.boss_append();

    _itemList->resetIndex();
    updateList();
}

void CharacterEditor::del()
{
    int index = _itemList->index();
    if(index == -1) { TransparentDialog::play(this, "未选中项目"); return; }
    if(roundButton[0]->isChecked()) db.hero_delete( _itemList->getItem(index).text[0].toInt());
    if(roundButton[1]->isChecked()) db.enemy_delete(_itemList->getItem(index).text[0].toInt());
    if(roundButton[2]->isChecked()) db.boss_delete( _itemList->getItem(index).text[0].toInt());

    _itemList->resetIndex();
    updateList();
}



