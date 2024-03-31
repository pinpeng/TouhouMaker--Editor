#ifndef CACHE_AGENT_H
#define CACHE_AGENT_H

#include <QList>
#include <QStack>
#include <QMap>

#include <QFile>
#include <QDir>
#include <QtMath>

#include "dataSet/memoryCache/database.h"
#include "dataSet/editorSetting.h"
#include "sprite.h"
#include "draw.h"

#include <QPixmap>
#include <QMovie>

struct sprite_buff {
    QPixmap png;
    QMovie *gif = nullptr;

    sprite_buff() {};
};

class CacheAgent
{
    public:
    CacheAgent();
    static CacheAgent& getInstance();

    void databaseInit(QString _name, QString _position);
    void databaseUpdate(Database db);
    void databaseClean();

    bool databaseUndo();
    bool databaseRedo();

    int databaseLanSize();

    public:
    EditorSetting setting;

    int stage_id_top;
    int stage_event_id_top;

    int text_id_top;

    int hero_id_top;
    int enemy_id_top;
    int boss_id_top;

    int bullet_id_top;
    int effect_id_top;

    int audio_id_top;
    int image_id_top;

    int               database_list_max_size;
    QStack<Database>  database_list;
    QStack<Database>  database_list_last;

    Database         database();
    Database_info    databaseInfo();

    QMap<QString, sprite_buff> sprite_buffer;

};

#endif // CACHE_AGENT_H


