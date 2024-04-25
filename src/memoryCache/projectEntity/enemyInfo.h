#ifndef MEMORY_CACHE_ENEMY_INFO_H
#define MEMORY_CACHE_ENEMY_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QString>
#include <QMap>

namespace MemoryCache{
    class EnemyInfo:public IMemoryData{
        public:
        EnemyInfo();
        EnemyInfo(int id,int charaId,int bulletId);
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;
        public:
        int _enemyId;
        int _characterId;
        int _bulletId;
        // TODO... 后续拆分该结构
        QMap<QString,float> data;
        QMap<QString,QString> data_str;
    };
}

#endif