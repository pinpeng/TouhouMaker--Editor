#include "window_find_dictionary.h"

Window_find_dictionary::Window_find_dictionary(Database *_db, QWidget *parent) : Window_small(parent)
{
    setFixedSize(1200, 800);
    setWindowTitle("搜索文本");

    db = _db;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32, 64, 960 - 64, 80);
    lineEdit->setText("");

    button_find = new Widget_Button(this);
    button_find->setGeometry(960 - 32, 64, 240, 80);
    button_find->setText("搜索");
    button_find->setTimer(timer);

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(32, 144, 1200 - 64, 640 - 16);
    itemList->setHeadSize(128, 700);
    //itemList->setShowIcon();

    connect(button_find, SIGNAL(pressed()), this, SLOT(find()));
    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(getPosition(int)));
}

void Window_find_dictionary::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
}

void Window_find_dictionary::find()
{
    QList<itemSTR> tmpList;
    QString tmp = lineEdit->text();
    QMap<int, DB_Dictionary_File>::iterator i = db->dictionary_file.begin();
    while(i != db->dictionary_file.end()) {
        QString name = i.value().name;
        QString faName = db->dictionary_folder[i.value().fa].name + "/";
        name = faName + name;
        if(name.indexOf(tmp) != -1) {
            if(name.size() > 20) name = "..." + name.right(20);
            tmpList += itemSTR(nullptr, QString::number(i.key()), name, "文本");
        }
        i ++;
    }
    for(int k = 0; k < db->dictionary_folder.size(); k ++) {
        QString name = db->dictionary_folder[k].name;
        if(name.indexOf(tmp) != -1) {
            if(name.size() > 20) name = "..." + name.right(20);
            tmpList += itemSTR(nullptr, QString::number(k), name, "文件夹");
        }
    }
    itemList->setItems(tmpList);
    Message_Box::play(this, "找到" + QString::number(tmpList.size()) + "项");
}

void Window_find_dictionary::getPosition(int pos)
{
    emit doubleClicked(itemList->getItem(pos).id.toInt());
    end();
}
