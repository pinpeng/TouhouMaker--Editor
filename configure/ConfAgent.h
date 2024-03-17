#ifndef CONFAGENT_H
#define CONFAGENT_H

#include "configure/fontManager.h"

class ConfAgent{
public:
    static ConfAgent& GetInstance();
    const QFont& GetFont(const QString& fontName);
private:
    Configure::FontManager _fontManager;
};

#endif // CONFAGENT_H
