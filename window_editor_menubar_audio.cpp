#include "window_editor_menubar_audio.h"

#include "qdesktopservices.h"

#include "global.h"
#include <QApplication>
#include <qt_windows.h>
#include <QDesktopWidget>

Window_editor_menubar_audio::Window_editor_menubar_audio(QWidget *parent) : Window_small(parent)
{
    QRect rect = QApplication::desktop()->screenGeometry();

    if(rect.height() > 150)
    {
        setFixedSize(1200, rect.height() - 150);
    }
    else
    {
        setFixedSize(1200, 900);
    }
    setWindowTitle("编辑音频");

    db = Global::database();

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(720 - 28, rect.height() - 150 - 96, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(960 - 20, rect.height() - 150 - 96, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));


    QString _text[3] = { "背景音乐", "音效", "剧情配音" };

    select_group = new QButtonGroup(this);
    for(int i = 0; i < 3; i ++) {
        roundButton[i] = new Widget_RoundButton(this);
        roundButton[i]->setText(_text[i]);
        roundButton[i]->setGeometry(48 + 180 * i, 84, 180, 60);
        roundButton[i]->setTimer(timer);
        select_group->addButton(roundButton[i]);
        connect(roundButton[i], SIGNAL(stateChanged()), this, SLOT(updateList()));
    }

    button_openFolder = new Widget_Button(this);
    button_openFolder->setTimer(timer);
    button_openFolder->setText("打开音频文件夹");
    button_openFolder->setGeometry(816, 64, 400 - 36, 80);
    connect(button_openFolder, SIGNAL(pressed()), this, SLOT(openFolder()));

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1200 - 36, rect.height() - 150 - 320);

    button_add = new Widget_Button(this);
    button_del = new Widget_Button(this);
    button_add->setGeometry(12, rect.height() - 150 - 176 , 580, 80);
    button_add->setText("新建");
    button_add->setTimer(timer);
    button_del->setGeometry(600, rect.height() - 150 - 176 , 580, 80);
    button_del->setText("删除");
    button_del->setTimer(timer);

    connect(button_add, SIGNAL(pressed()), this, SLOT(add()));
    connect(button_del, SIGNAL(pressed()), this, SLOT(del()));

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(editAudio(int)));

    roundButton[0]->setChecked(true);
    updateList();
}

void Window_editor_menubar_audio::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_editor_menubar_audio::updateList()
{
    QList<itemSTR> tmpList;
    QList<QString> text_list;
    text_list << "ID" << "名称" << "状态";
    itemList->setHeadTextList(text_list);
    itemList->setHeadWidthList({120, 720, 240});

    int tmp = -1;
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) tmp = i;

    for(auto i = db.audio[tmp].begin(); i != db.audio[tmp].end(); i ++) {
        itemSTR tmp_item;
        tmp_item.text.append(QString::number(i.value().__id));
        tmp_item.text.append(i.value().name);
        tmp_item.text.append(state_arr[i.value().state]);
        tmpList.append(tmp_item);
    }
    itemList->setItemList(tmpList);
}

void Window_editor_menubar_audio::accept()
{
    Global::databaseUpdate(db);
    end();
}

void Window_editor_menubar_audio::editAudio(int _index)
{
    if(_index == -1) return;
    if(itemList->index() == -1) return;

    editAudioStart(itemList->getItem(_index).text[0].toInt());
}

void Window_editor_menubar_audio::openFolder()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(Global::databaseInfo().projectPosition + "/audio"))) {
        Message("无法打开文件夹");
    }
}

void Window_editor_menubar_audio::editAudioStart(int _index)
{

    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) {
        window_editor = new Window_editor_menubar_audio_edit(&db, &db.audio[i][_index]);
        connect(window_editor, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor->setWindowModality(Qt::ApplicationModal);
        window_editor->setAttribute(Qt::WA_DeleteOnClose);
        window_editor->show();
    }

}

void Window_editor_menubar_audio::add()
{
    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.audio_append(i);

    itemList->resetIndex();
    updateList();
}

void Window_editor_menubar_audio::del()
{
    int index = itemList->index();
    if(index == -1) { Message_Box::play(this, "未选中项目"); return; }

    for(int i = 0; i < 3; i ++) if(roundButton[i]->isChecked()) db.audio_delete(i, itemList->getItem(index).text[0].toInt());

    itemList->resetIndex();
    updateList();
}


