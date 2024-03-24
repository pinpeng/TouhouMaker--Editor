#ifndef SOURCE_AGENT_H
#define SOURCE_AGENT_H

#include "globalSource/fontManager.h"
#include "globalSource/timerManager.h"

class SourceAgent{
public:
    static SourceAgent& GetInstance();
    const QFont& GetFont(const QString& fontName);
    const QSharedPointer<QTimer>& GetTimer(const QString& timerName);
private:
    GlobalSource::FontManager _fontManager;
    GlobalSource::TimerManager _timerManager;
};

#endif // SOURCE_AGENT_H
