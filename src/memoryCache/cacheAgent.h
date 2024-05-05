#ifndef CACHE_AGENT_H
#define CACHE_AGENT_H

#include <QList>
#include <QMap>

#include <QFile>
#include <QDir>
#include <QtMath>
#include <QPixmap>
#include <QMovie>

#include "memoryCache/projectEntity/projectData.h"
#include "memoryCache/globalEntity/editorSetting.h"
#include "sprite.h"
#include "draw.h"



struct sprite_buff {
    QPixmap png;
    QMovie *gif = nullptr;

    sprite_buff() {};
};

class CacheAgent
{
    public:
    int stage_id_top = 100;
    int stage_event_id_top = 100;

    int text_id_top = 100;
    int hero_id_top = 100;
    int enemy_id_top = 100;
    int boss_id_top = 100;
    int bullet_id_top = 100;

    int effect_id_top = 100;
    int audio_id_top = 100;
    public:
    CacheAgent();
    static CacheAgent& getInstance();

    void databaseInit(const QString& projectName,const QString& projectDir);
    void databaseUpdate(ProjectData db);
    void databaseClean();

    bool databaseUndo();
    bool databaseRedo();

    int databaseLanSize();

    bool saveToDatabase();
    bool initFromDatabase();

    public:
    MemoryCache::EditorSetting setting;

    QList<ProjectData> _databaseList;              // 数据库列表，用于进行撤销/还原操作
    int _curDbIndex;                            // 当前数据库指针
    
    ProjectData         database();
    Database_info    databaseInfo();
};

#endif // CACHE_AGENT_H


