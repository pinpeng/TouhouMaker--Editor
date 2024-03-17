#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>
#include <QList>

struct Spr
{
    static QList<QPixmap> sprite;
    static void init();
    static void release();

    static QList<QPixmap> sprite_event_icon;
    static QList<QPixmap> sprite_menu_func;

#define Sprite(_str) Spr::get(Spr::_str)
    static QPixmap get(int index);
#define SpriteIndex(_str) Spr::getIndex(Spr::_str);
    static QPixmap* getIndex(int index);

    enum sprites {
        icon_folder,
        icon_file,
        icon_video,

        icon_runner0,
        icon_runner1,
        icon_runner2,
        icon_runner3,

        logo_mscb,
        logo_msc,

        ui_author_web,
        ui_background,
        ui_ban_area,

        tips_normal,
        tips_happy,
        tips_sleep,
        tips_dark_face,
        tips_worry,
        tips_shy
    };

};

#endif // SPRITE_H


