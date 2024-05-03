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

        inline ThemeStyle themeStyle() const {
            return _themeStyle;
        }

        inline void SetThemeStyle(ThemeStyle style){
            _themeStyle = style;
        }

        inline QString lastProjectPath() const {
            return _lastProjectPath;
        }

        inline void setLastProjectPath(const QString& path){
            _lastProjectPath = path;
        }

        inline QString lastProjectName() const {
            return _lastProjectName;
        }

        inline void setLastProjectName(const QString& name){
            _lastProjectName = name;
        }

        inline void setLastProject(const QString& path,const QString& name){
            _lastProjectPath = path;
            _lastProjectName = name;
        }

        inline float editorScale() const{
            return _editorScale;
        }

        inline void setEditorScale(const float scale){
            _editorScale = scale;
        }

        inline float timelineScale() const {
            return _timelineScale;
        }

        inline void setTimelineScale(const float scale){
            _timelineScale = scale;
        }

        inline bool isAntialising() const {
            return _isAntialising;
        }

        inline void setAntialising(bool anti){
            _isAntialising = anti;
        }

        inline bool isScaleSet() const {
            return _isScaleSet;
        }

        inline void setScaleSet(bool scale){
            _isScaleSet = scale;
        }

        inline int isTipsShow() const{
            return _isTipsShow;
        }

        inline void setTipsShow(int tips){
            _isTipsShow = tips;
        }

        private:
        QSharedPointer<QSettings> _iniFile;
        ThemeStyle _themeStyle;
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