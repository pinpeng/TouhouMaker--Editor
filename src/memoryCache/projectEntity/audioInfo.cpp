#include "memoryCache/projectEntity/audioInfo.h"

namespace MemoryCache{
    AudioInfo::AudioInfo()
    :_audioId(0),_audioName(""){}

    AudioInfo::AudioInfo(int id,const QString& name)
    :_audioId(id),_audioName(name){}


    QJsonObject AudioInfo::serialize(){
        QJsonObject jsonObj;
        jsonObj.insert("audioId",_audioId);
        jsonObj.insert("audioName",_audioName);
        return jsonObj;
    }

    void AudioInfo::deserialize(QJsonObject& obj){
        if(obj.contains("audioId")){
            _audioId = obj.value("audioId").toInt();
            _audioName = obj.value("audioName").toString();
        }
    }
}