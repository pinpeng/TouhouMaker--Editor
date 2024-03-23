#include "configure/ConfAgent.h"

ConfAgent& ConfAgent::GetInstance(){
    static ConfAgent agent;
    return agent;
}

const QFont& ConfAgent::GetFont(const QString& fontName){
    return _fontManager.GetFont(fontName);
}



