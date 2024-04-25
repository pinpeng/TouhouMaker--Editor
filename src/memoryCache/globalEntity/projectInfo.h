#ifndef MEMORY_CACHE_PROJECT_INFO_H
#define MEMORY_CACHE_PROJECT_INFO_H

#include <QString>
#include "memoryCache/interface/IMemoryData.h"

namespace MemoryCache{
    class ProjectInfo:public IMemoryData{
        public:
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;
        public:
        QString projectName;
        QString projectPosition;
    };
}

#endif