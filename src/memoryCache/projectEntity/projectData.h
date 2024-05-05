#ifndef MEMORY_CACHE_MEMORY_DATA
#define MEMORY_CACHE_MEMORY_DATA

#include <QMap>
#include <QString>

#include "memoryCache/projectEntity/audioInfo.h"
#include "memoryCache/projectEntity/bulletInfo.h"
#include "memoryCache/projectEntity/characterInfo.h"
#include "memoryCache/projectEntity/enemyInfo.h"
#include "memoryCache/projectEntity/imageInfo.h"
#include "memoryCache/projectEntity/playerInfo.h"
#include "memoryCache/projectEntity/textInfo.h"

#include "database_main.h"
#include "database_define.h"
#include "database_info.h"

enum BulletType{
    BOSS,
    ENEMY,
    PLAYER
};

enum AudioType{
    BGM,
    SE,
    VOICE
};

enum ImageType{
    BACKGROUND,
    EFFECT,
    CHARACTER,
    BULLET,
    OTHER
};

// class ProjectData:public MemoryCache::IMemoryData{
//     public:
//     virtual QJsonObject serialize() override;
//     virtual void deserialize(QJsonObject& obj) override;
//     public:
//     // QMap<int,MemoryCache::TextInfo> _textMap;
//     QMap<int,MemoryCache::PlayerInfo> _playerMap;
//     QMap<int,MemoryCache::EnemyInfo> _enemyMap;
//     QMap<BulletType,QMap<int,MemoryCache::BulletInfo>> _bulletMap;
//     QMap<AudioType,QMap<int,MemoryCache::AudioInfo>> _audioMap;
//     QMap<ImageType,QMap<int,MemoryCache::ImageInfo>> _imageMap;
// };

// 需要考虑从磁盘中初始化时的数据状态
class ProjectData
{
    public:
    void clear();
    void init();
    bool read(QString basePath);
    bool save();
    bool pack();

    int text_append(QString _text);
    void text_delete(int _index);

    void setText(int _index, int _lan, QString _text);
    QString getText(int _index, int _lan);

    void stage_append(int _type, QString _name);
    void stage_delete_id(int _type, int _id);

    void hero_append(QString _name = "新建自机");
    void hero_delete(int _id);

    void enemy_append(QString _name = "新建敌机");
    void enemy_delete(int _id);

    void boss_append(QString _name = "新建BOSS");
    void boss_delete(int _id);

    void bullet_append(int _type, QString _name = "新建子弹");
    void bullet_delete(int _type, int _id);

    void effect_append(int _type, QString _name = "新建特效");
    void effect_delete(int _type, int _id);

    void audio_append(int _type, QString _name = "新建音频");
    void audio_delete(int _type, int _id);

    int addImage(ImageType type, QString _name = "新建图像");
    MemoryCache::ImageInfo* getImage(ImageType type,int imageId);
    QMap<int,MemoryCache::ImageInfo>& getImageMap(ImageType type);
    void deleteImage(ImageType type, int imageId);
    bool isImageValid(ImageType type,int imageId);

    ProjectData();
    ProjectData(QString _name, QString _position);

    void projectInitBase();
    void projectInitEmpty();
    void projectInitExample();

    int lanSize();

    public:
    Database_info info;

    QMap<int, DB_text>              text;

    QList<DB_UI_TITLE>              ui_title;

    QList<DB_STAGE>                 stage[2]; // normal, ex

    QMap<int, DB_hero>              hero;
    QMap<int, DB_enemy>             enemy;
    QMap<int, DB_boss>              boss;

    QMap<int, DB_bullet>            bullet[3]; // boss, enemy, hero

    QMap<int, DB_effect>            effect[3]; // bullet, background, character

    QMap<int, DB_audio>             audio[3]; // bgm, se, voice

    /**
     * @brief 图片存储结构，ImageType-图像类型，int-图片索引，ImageInfo-图片数据
     * @brief 注意本结构体中并不真正存储图片，而是存储图片指向路径
    */
    QMap<ImageType,QMap<int,MemoryCache::ImageInfo>> _imageMap;
    // QMap<int, MemoryCache::ImageInfo>             image[5]; // background, effect, story character, bullet, other
};

#endif