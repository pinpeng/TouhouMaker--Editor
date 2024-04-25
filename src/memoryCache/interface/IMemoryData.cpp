#include "memoryCache/interface/IMemoryData.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QByteArray>

namespace MemoryCache{
    QString IMemoryData::toJsonString(){
        QJsonObject jsonObj = serialize();
        QJsonDocument document;
        document.setObject(jsonObj);
        
        QByteArray byteArray = document.toJson(QJsonDocument::Compact);
        QString strJson(byteArray);

        return strJson;
    }

    void IMemoryData::fromJsonString(const QString& jsonStr){
        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson(jsonStr.toStdString().data(),&jsonError);
        if(!document.isNull() && jsonError.error == QJsonParseError::NoError){
            if(document.isObject()){
                QJsonObject jsonObj = document.object();
                deserialize(jsonObj);
            }
        }
    }
}