#include "memoryCache/globalEntity/editorSetting.h"
#include <QSettings>
#include <QTextCodec>
#include <QFile>

namespace MemoryCache{
    EditorSetting::EditorSetting(const QString& filePath)
    :IFileOperator(filePath){
        _iniFile = QSharedPointer<QSettings>::create(_filePath,QSettings::IniFormat);
        _iniFile->setIniCodec(QTextCodec::codecForName("UTF-8"));
        if(QFile::exists(_filePath)){
            ReadFromFile();
        }
        else{
            // 读取默认参数
            ReadFromFile();
            SaveToFile();
        }
    }

    bool EditorSetting::SaveToFile(){
        _iniFile->setValue("global/color_group", static_cast<int>(_themeStyle));
        _iniFile->setValue("global/last_path", _lastProjectPath);
        _iniFile->setValue("global/last_name", _lastProjectName);

        _iniFile->setValue("editor/scale", _editorScale);

        _iniFile->setValue("stage/view_scale", _timelineScale);
        _iniFile->setValue("stage/antialising", _isAntialising);

        _iniFile->setValue("global/SFTS", _isScaleSet);

        _iniFile->setValue("tips/action", _isTipsShow);

        _iniFile->sync();
    }

    bool EditorSetting::ReadFromFile(){
        _themeStyle = static_cast<ThemeStyle>(_iniFile->value("global/color_group", 0).toInt());
        _lastProjectPath = _iniFile->value("global/last_path", 0).toString();
        _lastProjectName = _iniFile->value("global/last_name", 0).toString();

        _editorScale = _iniFile->value("editor/scale", 1.0).toFloat();

        _timelineScale = _iniFile->value("stage/view_scale", 100.0).toFloat();
        _isAntialising = _iniFile->value("stage/antialising", true).toBool();

        _isScaleSet = _iniFile->value("global/SFTS", 0).toInt();

        _isTipsShow = _iniFile->value("tips/action", 0).toInt();
    }
}