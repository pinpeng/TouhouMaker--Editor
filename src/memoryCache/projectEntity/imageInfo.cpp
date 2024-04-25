#include "memoryCache/projectEntity/imageInfo.h"
#include <QJsonObject>


namespace MemoryCache{
    ImageInfo::ImageInfo():_imageId(0),_imageName(""),_imageType(ImageType::UNKNOWN)
    {}

    ImageInfo::ImageInfo(int imageId,const QString& imageName,ImageType type)
    :_imageId(imageId),_imageName(imageName),_imageType(type){}

    QJsonObject ImageInfo::serialize(){
        QJsonObject json;

        json.insert("imageId",_imageId);
        json.insert("imageName",_imageName);
        json.insert("imageType",_imageType);

        return json;
    }

    void ImageInfo::deserialize(QJsonObject& obj){                
        if(obj.contains("imageId")){
            _imageId = obj.value("imageId").toInt();
            _imageName = obj.value("imageName").toString();
            _imageType = static_cast<ImageType>(obj.value("imageType").toInt());
        }
    }
}