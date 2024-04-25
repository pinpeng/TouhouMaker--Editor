#ifndef MEMORY_CACHE_MEMORY_DATA
#define MEMORY_CACHE_MEMORY_DATA

#include "memoryCache/projectEntity/audioInfo.h"
#include "memoryCache/projectEntity/bulletInfo.h"
#include "memoryCache/projectEntity/characterInfo.h"
#include "memoryCache/projectEntity/enemyInfo.h"
#include "memoryCache/projectEntity/imageInfo.h"
#include "memoryCache/projectEntity/playerInfo.h"
#include "memoryCache/projectEntity/textInfo.h"

#include <QMap>
#include <QString>

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

class ProjectData:public MemoryCache::IMemoryData{
    public:
    virtual QJsonObject serialize() override;
    virtual void deserialize(QJsonObject& obj) override;
    public:
    // QMap<int,MemoryCache::TextInfo> _textMap;
    QMap<int,MemoryCache::PlayerInfo> _playerMap;
    QMap<int,MemoryCache::EnemyInfo> _enemyMap;
    QMap<BulletType,QMap<int,MemoryCache::BulletInfo>> _bulletMap;
    QMap<AudioType,QMap<int,MemoryCache::AudioInfo>> _audioMap;
    QMap<ImageType,QMap<int,MemoryCache::ImageInfo>> _imageMap;
};

#endif