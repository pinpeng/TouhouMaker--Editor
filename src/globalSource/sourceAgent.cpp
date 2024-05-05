#include "globalSource/sourceAgent.h"

SourceAgent& SourceAgent::getInstance(){
    static SourceAgent agent;
    return agent;
}

const QFont& SourceAgent::getFont(const QString& fontName){
    return _fontManager.getFont(fontName);
}

const QSharedPointer<QTimer>& SourceAgent::getTimer(const QString& timerName){
    return _timerManager.getTimer(timerName);
}

bool SourceAgent::getImage(const QString& key,QSharedPointer<QPixmap> pngImage){
    return _imageManager.getImage(key,pngImage);
}

bool SourceAgent::getImage(const QString& key,QSharedPointer<QMovie> gifImage){
    return _imageManager.getImage(key,gifImage);
}

bool SourceAgent::setImage(const QString& key,QSharedPointer<QPixmap> pngImage){
    return _imageManager.setImage(key,pngImage);
}

bool SourceAgent::setImage(const QString& key,QSharedPointer<QMovie> gifImage){
    return _imageManager.setImage(key,gifImage);
}