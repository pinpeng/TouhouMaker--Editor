#include "memoryCache/projectEntity/characterInfo.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

namespace MemoryCache{
    CharacterInfo::CharacterInfo()
    :_charaId(0),_charaName(""){}

    CharacterInfo::CharacterInfo(int id,const QString& name,const QMap<QString,QString>& imgMap)
    :_charaId(id),_charaName(name),_imageNameList(imgMap){}
    
    QJsonObject CharacterInfo::serialize(){
        QJsonObject json;
        json.insert("characterId",_charaId);
        json.insert("characterName",_charaName);
        json.insert("imageNameList",serializeImageList());
    }

    void CharacterInfo::deserialize(QJsonObject& obj){
        if(obj.contains("characterId")){
            _charaId = obj.value("characterId").toInt();
            _charaName = obj.value("characterName").toString();
            QJsonObject imgObj = obj.value("imageNameList").toObject();
            deserialize(imgObj);
        }
    }

    QJsonObject CharacterInfo::serializeImageList(){
        // QJsonObject json;
        // for(const auto& i: _imageNameList){
        //     json.insert(i.first,i.second);
        // }
        // return json;
    }

    void CharacterInfo::deserializeImageList(QJsonObject& obj){
        for(auto i = obj.begin();i != obj.end(); ++i){
            _imageNameList[i.key()] = i.value().toString();
        }
    }
}