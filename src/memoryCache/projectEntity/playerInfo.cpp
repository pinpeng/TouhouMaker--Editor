#include "memoryCache/projectEntity/playerInfo.h"

namespace MemoryCache{
    PlayerInfo::PlayerInfo()
    :_playerId(0),_characterId(0),_bulletId(0){}
    
    PlayerInfo::PlayerInfo(int playerId,int charaId,int bulletId)
    :_playerId(playerId),_characterId(charaId),_bulletId(bulletId){}

    QJsonObject PlayerInfo::serialize(){
        QJsonObject obj;
        obj.insert("playerId",_playerId);
        obj.insert("characterId",_characterId);
        obj.insert("bulletId",_bulletId);
        return obj;
    }

    void PlayerInfo::deserialize(QJsonObject& obj){
        if(obj.contains("playerId")){
            _playerId = obj.value("playerId").toInt();
            _characterId = obj.value("characterId").toInt();
            _bulletId = obj.value("bulletId").toInt();
        }
    }
}