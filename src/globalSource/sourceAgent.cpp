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

