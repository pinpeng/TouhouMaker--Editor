#ifndef MEMORY_CACHE_CHARACTER_INFO_H
#define MEMORY_CACHE_CHARACTER_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QMap>
#include <QString>

namespace MemoryCache{
    const static QString CHARA_IMAGE_UP_LEFT = "upLeft";
    const static QString CHARA_IMAGE_UP = "up";
    const static QString CHARA_IMAGE_UP_RIGHT = "upRight";
    const static QString CHARA_IMAGE_LEFT = "left";
    const static QString CHARA_IMAGE_DEFAULT = "default";
    const static QString CHARA_IMAGE_RIGHT = "right";
    const static QString CHARA_IMAGE_DOWN_LEFT = "downLeft";
    const static QString CHARA_IMAGE_DOWN = "down";
    const static QString CHARA_IMAGE_DOWN_RIGHT = "downRight";

    class CharacterInfo:public IMemoryData{
        public:
        CharacterInfo();
        CharacterInfo(int id,const QString& name,const QMap<QString,QString>& imgMap);
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;

        private:
        QJsonObject serializeImageList();
        void deserializeImageList(QJsonObject& array);

        public:
        int _charaId;
        QString _charaName;
        QMap<QString,QString> _imageNameList;
        
    };
}

#endif