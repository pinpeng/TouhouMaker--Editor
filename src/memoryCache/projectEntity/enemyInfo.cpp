#include "memoryCache/projectEntity/enemyInfo.h"

namespace MemoryCache{
    EnemyInfo::EnemyInfo()
    :_enemyId(0),_characterId(0),_bulletId(0){}

    EnemyInfo::EnemyInfo(int id,int charaId,int bulletId)
    :_enemyId(id),_characterId(charaId),_bulletId(bulletId){}

    QJsonObject EnemyInfo::serialize(){
        QJsonObject json;
        
        json.insert("enemyId",_enemyId);
        json.insert("characterId",_characterId);
        json.insert("bulletId",_bulletId);

        return json;
    }

    void EnemyInfo::deserialize(QJsonObject& obj){
        if(obj.contains("enemyId")){
            _enemyId = obj.value("enemyId").toInt();
            _characterId = obj.value("characterId").toInt();
            _bulletId = obj.value("bulletId").toInt();
        }
    }
}