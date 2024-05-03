#include "globalSource/imageManager.h"

namespace GlobalSource{
    ImageManager::ImageManager(){

    }

    // ImageManager::InitFromDatabase(const ProjectData& db){
    //     throw "把database_save中read对图片缓存的处理移动到这里(263行)";
    // }

    bool ImageManager::getImage(const QString& key,QSharedPointer<QPixmap> pngImage){
        if(_pngMap.find(key) == _pngMap.end()){
            pngImage = nullptr;
            return false;
        }
        pngImage = _pngMap[key];
        return true;
    }

    bool ImageManager::getImage(const QString& key,QSharedPointer<QMovie> gifImage){
        if(_gifMap.find(key) == _gifMap.end()){
            gifImage = nullptr;
            return false;
        }
        gifImage = _gifMap[key];
        return true;
    }

    bool ImageManager::setImage(const QString& key,QSharedPointer<QPixmap> pngImage){
        _pngMap[key] = pngImage;
        return true;
    }

    bool ImageManager::setImage(const QString& key,QSharedPointer<QMovie> gifImage){
        _gifMap[key] = gifImage;
        return true;
    }
}