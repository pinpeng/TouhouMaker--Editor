#include "memoryCache/projectEntity/bulletInfo.h"

namespace MemoryCache{
    BulletInfo::BulletInfo():_bulletId(0),_bulletName(""),_bulletImageName("")
    {}

    BulletInfo::BulletInfo(int id,const QString& name,const QString& imageName)
    :_bulletId(id),_bulletName(name),_bulletImageName(imageName){}

    QJsonObject BulletInfo::serialize(){
        QJsonObject jsonObj;
        jsonObj.insert("bulletId",_bulletId);
        jsonObj.insert("bulletName",_bulletName);
        jsonObj.insert("bulletImageName",_bulletImageName);
        return jsonObj;
    }

    void BulletInfo::deserialize(QJsonObject& obj){
        if(obj.contains("bulletId")){
            _bulletId = obj.value("bulletId").toInt();
            _bulletName = obj.value("bulletName").toString();
            _bulletImageName = obj.value("bulletImageName").toString();
        }
    }
}