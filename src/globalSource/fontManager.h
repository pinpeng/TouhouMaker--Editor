#ifndef FONTMAANGER_H
#define FONTMAANGER_H

#include <QMap>
#include <QFont>
#include <QString>

namespace GlobalSource{
    const static QString FONT_DEFAULT                   = "default";
    const static QString FONT_JCYT_500W                 = "jcyt500W.ttf";

    class FontManager{
    public:
        FontManager();
        const QFont& GetFont(const QString& fontName);
    private:
        QString _fontFilePath;
        QMap<QString,QFont> _fontMap;
    };
}

#endif // FONTMAANGER_H
