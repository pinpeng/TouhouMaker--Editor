#ifndef MEMORY_CACHE_EDITOR_SETTING_H
#define MEMORY_CACHE_EDITOR_SETTING_H

#include <QString>
#include <QSharedPointer>
#include <QSettings>
#include "memoryCache/interface/IFileOperator.h"

namespace MemoryCache{
    enum ThemeStyle{
        DEFAULT = 0,
        GRAY = 1,
        DARK = 2,
        CUSTOM = 3
    };

    class EditorSetting:public IFileOperator{
        public:
        EditorSetting(const QString& filePath);
        virtual bool SaveToFile() override;
        virtual bool ReadFromFile() override;
        private:
        QSharedPointer<QSettings> _iniFile;

        ThemeStyle themeStyle;
        QString _lastProjectPath;
        QString _lastProjectName;
        float _editorScale;
        float _timelineScale;
        bool _isAntialising;
        bool _isScaleSet;
        int _isTipsShow;
        
    };
}

#endif