#include "window_find_audio.h"

Window_find_audio::Window_find_audio(Database *_db, QWidget *parent) : Window_small(parent)
{
    setFixedSize(1200, 848);
    setWindowTitle("搜索音频");

    db = _db;

    lineEdit = new EllipticalLineEdit(this);
    lineEdit->setGeometry(32, 64 + 48, 960 - 64, 80);
    lineEdit->setText("");

    button_find = new GradientButton(this);
    button_find->setGeometry(960 - 32, 64 + 48, 240, 80);
    button_find->setText("搜索");
    button_find->setTimer(_timer);

    buttonBox_type = new QButtonGroup(this);
    roundButton_all = new RoundButton(this);
    roundButton_1 = new RoundButton(this);
    roundButton_2 = new RoundButton(this);
    roundButton_3 = new RoundButton(this);
    buttonBox_type->addButton(roundButton_all);
    buttonBox_type->addButton(roundButton_1);
    buttonBox_type->addButton(roundButton_2);
    buttonBox_type->addButton(roundButton_3);

    roundButton_all->setText("所有");
    roundButton_all->setGeometry(64, 68, 180, 80);
    roundButton_all->setTimer(_timer);
    roundButton_all->setChecked(true);
    roundButton_1->setText("仅音乐");
    roundButton_1->setGeometry(64 + 180, 68, 180, 80);
    roundButton_1->setTimer(_timer);
    roundButton_2->setText("仅音效");
    roundButton_2->setGeometry(64 + 360, 68, 180, 80);
    roundButton_2->setTimer(_timer);
    roundButton_3->setText("仅配音");
    roundButton_3->setGeometry(64 + 540, 68, 180, 80);
    roundButton_3->setTimer(_timer);

    itemList = new ItemList(this);
    itemList->setGeometry(32, 144 + 48, 1200 - 64, 640 - 16);
    itemList->setHeadSize(128, 700);
    //itemList->setShowIcon();

    connect(button_find, SIGNAL(pressed()), this, SLOT(find()));
    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(getPosition(int)));
}

void Window_find_audio::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_find_audio::find()
{
    QList<itemSTR> tmpList;
    QString tmp = lineEdit->text();
    if(roundButton_all->isChecked() || roundButton_1->isChecked()) {
        QMap<int, DB_Audio_File>::iterator i = db->audio_bgm_file.begin();
        while(i != db->audio_bgm_file.end()) {
            QString name = i.value().name;
            QString faName = db->audio_bgm_folder[i.value().fa].name + "/";
            name = faName + name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(i.key()), name, type_arr[0]);
            }
            i ++;
        }
        for(int k = 0; k < db->audio_bgm_folder.size(); k ++) {
            QString name = db->audio_bgm_folder[k].name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(k), name, type_arr[1]);
            }
        }
    }
    if(roundButton_all->isChecked() || roundButton_2->isChecked()) {
        QMap<int, DB_Audio_File>::iterator i = db->audio_se_file.begin();
        while(i != db->audio_se_file.end()) {
            QString name = i.value().name;
            QString faName = db->audio_se_folder[i.value().fa].name + "/";
            name = faName + name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(i.key()), name, type_arr[2]);
            }
            i ++;
        }
        for(int k = 0; k < db->audio_se_folder.size(); k ++) {
            QString name = db->audio_se_folder[k].name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(k), name, type_arr[3]);
            }
        }
    }
    if(roundButton_all->isChecked() || roundButton_3->isChecked()) {
        QMap<int, DB_Audio_File>::iterator i = db->audio_voice_file.begin();
        while(i != db->audio_voice_file.end()) {
            QString name = i.value().name;
            QString faName = db->audio_voice_folder[i.value().fa].name + "/";
            name = faName + name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(i.key()), name, type_arr[4]);
            }
            i ++;
        }
        for(int k = 0; k < db->audio_voice_folder.size(); k ++) {
            QString name = db->audio_voice_folder[k].name;
            if(name.indexOf(tmp) != -1) {
                if(name.size() > 20) name = "..." + name.right(20);
                tmpList += itemSTR(nullptr, QString::number(k), name, type_arr[5]);
            }
        }
    }

    itemList->setItems(tmpList);
    TransparentDialog::play(this, "找到" + QString::number(tmpList.size()) + "项");
}

void Window_find_audio::getPosition(int pos)
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
