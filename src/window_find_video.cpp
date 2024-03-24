#include "window_find_video.h"

Window_find_video::Window_find_video(Database *_db, QWidget *parent) : Window_small(parent)
{
    setFixedSize(1200, 848);
    setWindowTitle("搜索视频");

    db = _db;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32, 64 + 48, 960 - 64, 80);
    lineEdit->setText("");

    button_find = new Widget_Button(this);
    button_find->setGeometry(960 - 32, 64 + 48, 240, 80);
    button_find->setText("搜索");
    button_find->setTimer(_timer);

    buttonBox_type = new QButtonGroup(this);
    roundButton_all = new Widget_RoundButton(this);
    roundButton_1 = new Widget_RoundButton(this);
    roundButton_2 = new Widget_RoundButton(this);
    roundButton_3 = new Widget_RoundButton(this);
    buttonBox_type->addButton(roundButton_all);
    buttonBox_type->addButton(roundButton_1);
    buttonBox_type->addButton(roundButton_2);
    buttonBox_type->addButton(roundButton_3);

    roundButton_all->setText("所有");
    roundButton_all->setGeometry(64, 68, 180, 80);
    roundButton_all->setTimer(_timer);
    roundButton_all->setChecked(true);
    roundButton_1->setText("仅长视频");
    roundButton_1->setGeometry(64 + 180, 68, 180, 80);
    roundButton_1->setTimer(_timer);
    roundButton_2->setText("仅短视频");
    roundButton_2->setGeometry(64 + 360, 68, 180, 80);
    roundButton_2->setTimer(_timer);
    roundButton_3->setText("仅脚本");
    roundButton_3->setGeometry(64 + 540, 68, 180, 80);
    roundButton_3->setTimer(_timer);

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(32, 144 + 48, 1200 - 64, 640 - 16);
    itemList->setHeadSize(128, 700);
    //itemList->setShowIcon();

    connect(button_find, SIGNAL(pressed()), this, SLOT(find()));
    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(getPosition(int)));
}

void Window_find_video::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_find_video::find()
{
    QList<itemSTR> tmpList;
    QString tmp = lineEdit->text();
    if(roundButton_all->isChecked() || roundButton_1->isChecked()) {
        QMap<int, DB_Video_File>::iterator i = db->video_long_file.begin();
        while(i != db->video_long_file.end()) {
            QString name = i.value().name;
            QString faName = db->video_long_folder[i.value().fa].name + "/";
            name = faName + name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(i.key()), name, type_arr[0]);
            }
            i ++;
        }
        for(int k = 0; k < db->video_long_folder.size(); k ++) {
            QString name = db->video_long_folder[k].name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(k), name, type_arr[1]);
            }
        }
    }
    if(roundButton_all->isChecked() || roundButton_2->isChecked()) {
        QMap<int, DB_Video_File>::iterator i = db->video_short_file.begin();
        while(i != db->video_short_file.end()) {
            QString name = i.value().name;
            QString faName = db->video_short_folder[i.value().fa].name + "/";
            name = faName + name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(i.key()), name, type_arr[2]);
            }
            i ++;
        }
        for(int k = 0; k < db->video_short_folder.size(); k ++) {
            QString name = db->video_short_folder[k].name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(k), name, type_arr[3]);
            }
        }
    }
    if(roundButton_all->isChecked() || roundButton_3->isChecked()) {
        QMap<int, DB_Video_File>::iterator i = db->video_script_file.begin();
        while(i != db->video_script_file.end()) {
            QString name = i.value().name;
            QString faName = db->video_script_folder[i.value().fa].name + "/";
            name = faName + name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(i.key()), name, type_arr[4]);
            }
            i ++;
        }
        for(int k = 0; k < db->video_script_folder.size(); k ++) {
            QString name = db->video_script_folder[k].name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(k), name, type_arr[5]);
            }
        }
    }

    itemList->setItems(tmpList);
    Message_Box::play(this, "找到" + QString::number(tmpList.size()) + "项");
}

void Window_find_video::getPosition(int pos)
{
    itemSTR item = itemList->getItem(pos);
    int tmp = item.id.toInt();
    for(int i = 0; i < 3; i ++) {
        if(item.text == type_arr[i * 2]) { tmp -= 100000000 * i; break; }
        if(item.text == type_arr[i * 2 + 1]) { tmp += 100000000 * i; break; }
    }
    emit doubleClicked(tmp);
    end();
}
