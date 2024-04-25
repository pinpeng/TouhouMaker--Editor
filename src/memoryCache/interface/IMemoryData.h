#ifndef MEMORY_CACHE_I_MEMORY_DATA
#define MEMORY_CACHE_I_MEMORY_DATA

#include <QString>
#include <QSharedPointer>
#include <QJsonObject>

namespace MemoryCache{
    class IMemoryData{
        public:
        virtual QString toJsonString();
        virtual void fromJsonString(const QString& jsonStr);

        virtual QJsonObject serialize() = 0;
        virtual void deserialize(QJsonObject& obj) = 0;
    };
}

#endif