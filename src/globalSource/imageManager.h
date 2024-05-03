#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <QMap>
#include <QString>
#include <QPixmap>
#include <QMovie>
#include <QSharedPointer>
// #include "dataSet/memoryCache/database.h"

namespace GlobalSource{
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