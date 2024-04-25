#ifndef MEMORY_CACHE_PLAYER_INFO_H
#define MEMORY_CACHE_PLAYER_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QString>

namespace MemoryCache{
    class PlayerInfo:public IMemoryData{
        public:
        PlayerInfo();
        PlayerInfo(int playerId,int charaId,int bulletId);
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;
        public:
        int _playerId;
        int _characterId;
        int _bulletId;
    };
}

#endif