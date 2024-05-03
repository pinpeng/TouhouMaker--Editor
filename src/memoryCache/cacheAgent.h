#ifndef CACHE_AGENT_H
#define CACHE_AGENT_H

#include <QList>
#include <QMap>

#include <QFile>
#include <QDir>
#include <QtMath>

#include "database.h"
#include "memoryCache/globalEntity/editorSetting.h"
#include "sprite.h"
#include "draw.h"

#include <QPixmap>
#include <QMovie>
#include "memoryCache/globalEntity/editorSetting.h"

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

    void databaseInit(const QString& projectName,const QString& projectDir);
    void databaseUpdate(Database db);
    void databaseClean();

    bool databaseUndo();
    bool databaseRedo();

    int databaseLanSize();

    bool saveToDatabase();
    bool initFromDatabase();

    public:
    MemoryCache::EditorSetting setting;

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

    QList<Database> _databaseList;              // 数据库列表，用于进行撤销/还原操作
    int _curDbIndex;                            // 当前数据库指针
    
    Database         database();
    Database_info    databaseInfo();
    QMap<QString, sprite_buff> sprite_buffer;

};

#endif // CACHE_AGENT_H


