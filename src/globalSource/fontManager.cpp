#include "globalSource/fontManager.h"
#include <QFontDatabase>
#include "toolkit/fileoperator.h"
#include "QtDebug"

namespace GlobalSource{
    FontManager::FontManager(){
        _fontFilePath = ToolKit::FileOperator::getEditorSubModulePath(ToolKit::FileModule::SOURCE_FONT);
        if(-1 == QFontDatabase::addApplicationFont(_fontFilePath.append(FONT_JCYT_500W))){
            qWarning() << "Cannot find font" << FONT_JCYT_500W << "in" << _fontFilePath;
        }
        QFont defaultFont;
        _fontMap[FONT_DEFAULT] = defaultFont;
    }

    const QFont& FontManager::getFont(const QString& fontName){
        if(_fontMap.end() != _fontMap.find(fontName)){
            return _fontMap[fontName];
        }
        qWarning() << "Cannot find font" << fontName;
        return _fontMap[FONT_DEFAULT];
    }
}
