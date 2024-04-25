#ifndef MEMORY_CACHE_STAGE_INFO_H
#define MEMORY_CACHE_STAGE_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QString>

namespace MemoryCache{
    class StageInfo:public IMemoryData{
        public:
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;
        public:
        int _stageId;
        QString _stageName;
        float length;
    };
}

#endif