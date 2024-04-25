#ifndef MEMORY_CACHE_IMAGE_INFO_H
#define MEMORY_CACHE_IMAGE_INFO_H

#include "memoryCache/interface/IMemoryData.h"
#include <QString>

namespace MemoryCache{
    enum ImageType{
        UNKNOWN,
        PNG,
        GIF
    };

    class ImageInfo : public IMemoryData
    {
        public:
        ImageInfo();
        ImageInfo(int imageId,const QString& imageName,ImageType type);
        ~ImageInfo() = default;
        virtual QJsonObject serialize() override;
        virtual void deserialize(QJsonObject& obj) override;
        private:
        int _imageId;
        // 既作为缓存名称，也作为磁盘文件名称
        QString _imageName;
        ImageType _imageType;
    };
}

#endif