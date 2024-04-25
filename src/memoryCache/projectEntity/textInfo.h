#ifndef MEMORY_CACHE_TEXT_INFO_H
#define MEMORY_CACHE_TEXT_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QJsonObject>
#include <QString>
#include <QList>

namespace MemoryCache{
    class TextInfo:public IMemoryData{
        public:
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;

        public:
        int _textId;
        QList<QString> _textList;
    };
}

#endif