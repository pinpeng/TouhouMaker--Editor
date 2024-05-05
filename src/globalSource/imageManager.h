#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <QMap>
#include <QString>
#include <QPixmap>
#include <QMovie>
#include <QSharedPointer>

namespace GlobalSource{
    /**
     * 图片缓存管理
     * TODO... 使用LRU算法避免内存爆炸
     * TODO... 添加从磁盘中初始化的方法
    */
    class ImageManager{
        public:
        ImageManager();
        // InitFromDatabase(const ProjectData& db);
        bool getImage(const QString& key,QSharedPointer<QPixmap> pngImage);
        bool getImage(const QString& key,QSharedPointer<QMovie> gifImage);
        bool setImage(const QString& key,QSharedPointer<QPixmap> pngImage);
        bool setImage(const QString& key,QSharedPointer<QMovie> gifImage);
        private:
        QMap<QString,QSharedPointer<QPixmap>> _pngMap;
        QMap<QString,QSharedPointer<QMovie>> _gifMap;
    };
}

#endif