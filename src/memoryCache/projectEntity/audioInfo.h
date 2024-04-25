#ifndef MEMORY_CACHE_AUDIO_INFO_H
#define MEMORY_CACHE_AUDIO_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QString>

namespace MemoryCache{
    class AudioInfo:public IMemoryData{
        public:
        AudioInfo();
        AudioInfo(int id,const QString& name);
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;

        public:
        int _audioId;
        QString _audioName;
    };
}

#endif