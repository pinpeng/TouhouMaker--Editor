#include "globalSource/sourceAgent.h"

SourceAgent& SourceAgent::GetInstance(){
    static SourceAgent agent;
    return agent;
}

const QFont& SourceAgent::GetFont(const QString& fontName){
    return _fontManager.GetFont(fontName);
}

const QSharedPointer<QTimer>& SourceAgent::GetTimer(const QString& timerName){
    return _timerManager.GetTimer(timerName);
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