// #include "window_find_character.h"

// Window_find_character::Window_find_character(Database *_db, QWidget *parent) : Window_small(parent)
// {
//     setFixedSize(1200, 800);
//     setWindowTitle("搜索角色");

//     db = _db;

//     lineEdit = new EllipticalLineEdit(this);
//     lineEdit->setGeometry(32, 64, 960 - 64, 80);
//     lineEdit->setText("");

//     button_find = new GradientButton(this);
//     button_find->setGeometry(960 - 32, 64, 240, 80);
//     button_find->setText("搜索");
//     button_find->setTimer(_timer);

//     itemList = new ItemList(this);
//     itemList->setGeometry(32, 144, 1200 - 64, 640 - 16);
//     itemList->setHeadSize(128, 700);
//     //itemList->setShowIcon();

//     connect(button_find, SIGNAL(pressed()), this, SLOT(find()));
//     connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(getPosition(int)));
// }

// void Window_find_character::paintEvent(QPaintEvent *)
// {
//     Draw::smallWindow(this, this);
// }

// void Window_find_character::find()
// {
//     int lan_size = db->info.language.size();

//     QList<itemSTR> tmpList;
//     QString tmp = lineEdit->text();
//     for(auto i = db->character_file.begin(); i != db->character_file.end(); i ++) {
//         QString faName = db->character_folder[i.value().fa].name + "/";
//         for(int j = 0; j < lan_size; j ++) {
//             QString name = i.value().name(j);
//             name = faName + name;
//             if(name.indexOf(tmp) != -1) {
//                 if(name.size() > 20) name = "..." + name.right(20);
//                 tmpList += itemSTR(nullptr, QString::number(i.key()), name, "角色");
//             }
//         }
//     }
//     for(int k = 0; k < db->character_folder.size(); k ++) {
//         QString name = db->character_folder[k].name;
//         if(name.indexOf(tmp) != -1) {
//             if(name.size() > 20) name = "..." + name.right(20);
//             tmpList += itemSTR(nullptr, QString::number(k), name, "文件夹");
//         }
//     }
//     itemList->setItems(tmpList);
//     TransparentDialog::play("找到" + QString::number(tmpList.size()) + "项");
// }

// void Window_find_character::getPosition(int pos)
// {
//     emit doubleClicked(itemList->getItem(pos).id.toInt());
//     end();
// }
