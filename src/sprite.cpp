#include "sprite.h"

#include <QApplication>

QList<QPixmap> Spr::sprite = QList<QPixmap>();
QList<QPixmap> Spr::sprite_event_icon = QList<QPixmap>();
QList<QPixmap> Spr::sprite_menu_func = QList<QPixmap>();

void Spr::init()
{
    sprite.insert(icon_folder,      QPixmap(":/ui/icon_folder.png"));
    sprite.insert(icon_file,        QPixmap(":/ui/icon_file.png"));
    sprite.insert(icon_video,       QPixmap(":/ui/icon_video.png"));

    sprite.insert(icon_runner0,     QPixmap(":/ui/icon_runner0.png"));
    sprite.insert(icon_runner1,     QPixmap(":/ui/icon_runner1.png"));
    sprite.insert(icon_runner2,     QPixmap(":/ui/icon_runner2.png"));
    sprite.insert(icon_runner3,     QPixmap(":/ui/icon_runner3.png"));

    sprite.insert(logo_mscb,        QPixmap(":/logo/mscb.png"));
    sprite.insert(logo_msc,         QPixmap(":/logo/msc.png"));
    sprite.insert(ui_author_web,    QPixmap(":/ui/check_here.png"));
    sprite.insert(ui_background,    QPixmap(":/ui/background.png"));
    sprite.insert(ui_ban_area,      QPixmap(":/ui/ban_area1.png"));

    sprite.insert(tips_normal,      QPixmap());//QApplication::applicationDirPath() + "/tips/tips0.png"));
    sprite.insert(tips_happy,       QPixmap());//QApplication::applicationDirPath() + "/tips/tips0.png"));
    sprite.insert(tips_sleep,       QPixmap());//QApplication::applicationDirPath() + "/tips/tips1.png"));
    sprite.insert(tips_dark_face,   QPixmap());//QApplication::applicationDirPath() + "/tips/tips2.png"));
    sprite.insert(tips_worry,       QPixmap());//QApplication::applicationDirPath() + "/tips/tips3.png"));
    sprite.insert(tips_shy,         QPixmap());//QApplication::applicationDirPath() + "/tips/tips4.png"));

    for(int i = 0; i < 16; i ++) {
        sprite_event_icon.append(QPixmap(":/event_icons/icons/thmk_event_icon" + QString::number(i + 1) + ".png"));
    }
    for(int i = 0; i < 12; i ++) {
        sprite_menu_func.append(QPixmap(":/menu_func/func/thmk_menu_func" + QString::number(i + 1) + ".png"));
    }
}

void Spr::release()
{

}

QPixmap Spr::get(int index)
{
    return sprite[index];
}

QPixmap* Spr::getIndex(int index)
{
    return &sprite[index];
}


