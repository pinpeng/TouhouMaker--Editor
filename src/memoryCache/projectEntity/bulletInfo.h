#ifndef MEMORY_CACHE_BULLET_INFO_H
#define MEMORY_CACHE_BULLET_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QString>
#include <QMap>

namespace MemoryCache{
    class BulletInfo:public IMemoryData
    {
        public:
        BulletInfo();
        BulletInfo(int id,const QString& name,const QString& imageName);

        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;

        public:
        int _bulletId;
        QString _bulletName;
        QString _bulletImageName;
        // TODO... 后续拆掉，不要用这么零散的数据结构
        QMap<QString,float> _bulletData;
        QMap<QString,QString> _bulletStrData;
    };
}

#endif