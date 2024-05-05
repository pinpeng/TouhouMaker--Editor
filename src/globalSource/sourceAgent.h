#ifndef SOURCE_AGENT_H
#define SOURCE_AGENT_H

#include "globalSource/fontManager.h"
#include "globalSource/timerManager.h"
#include "globalSource/imageManager.h"

class SourceAgent{
public:
    static SourceAgent& getInstance();
    const QFont& getFont(const QString& fontName);
    const QSharedPointer<QTimer>& getTimer(const QString& timerName);
    
    bool getImage(const QString& key,QSharedPointer<QPixmap> pngImage);
    bool getImage(const QString& key,QSharedPointer<QMovie> gifImage);
    bool setImage(const QString& key,QSharedPointer<QPixmap> pngImage);
    bool setImage(const QString& key,QSharedPointer<QMovie> gifImage);
private:
    GlobalSource::FontManager _fontManager;
    GlobalSource::TimerManager _timerManager;
    GlobalSource::ImageManager _imageManager;
};

#endif // SOURCE_AGENT_H
