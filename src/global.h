#ifndef GLOBAL_H
#define GLOBAL_H

#include <QList>
#include <QStack>
#include <QMap>

#include <QFile>
#include <QDir>
#include <QtMath>

#include "dataSet/database/database.h"
#include "setting.h"
#include "sprite.h"
#include "draw.h"

#include <QPixmap>
#include <QMovie>

#define lerp(x,y,val) (x*(1.0-val)+y*val)

struct sprite_buff {
    QPixmap png;
    QMovie *gif = nullptr;

    sprite_buff() {};
};

struct Global
{

    static Setting setting;

    static int stage_id_top;
    static int stage_event_id_top;

    static int text_id_top;

    static int hero_id_top;
    static int enemy_id_top;
    static int boss_id_top;

    static int bullet_id_top;
    static int effect_id_top;

    static int audio_id_top;
    static int image_id_top;

    static int               database_list_max_size;
    static QStack<Database>  database_list;
    static QStack<Database>  database_list_last;

    static Database         database();
    static Database_info    databaseInfo();

    static void databaseInit(QString _name, QString _position);
    static void databaseUpdate(Database db);
    static void databaseClean();

    static bool databaseUndo();
    static bool databaseRedo();

    static int databaseLanSize();

    static QMap<QString, sprite_buff> sprite_buffer;

};

#endif // GLOBAL_H


