#include "memoryCache/globalEntity/editorSetting.h"
#include <QSettings>
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
        _iniFile->setValue("global/color_group", themeStyle);
        _iniFile->setValue("global/last_path", _lastProjectPath);
        _iniFile->setValue("global/last_name", _lastProjectName);

        _iniFile->setValue("editor/scale", _editorScale);

        _iniFile->setValue("stage/view_scale", _timelineScale);
        _iniFile->setValue("stage/antialising", _isAntialising);

        _iniFile->setValue("global/SFTS", _isScaleSet);

        _iniFile->setValue("tips/action", _isTipsShow);
    }

    bool EditorSetting::ReadFromFile(){
        themeStyle = file->value("global/color_group", 0).toInt();
        _lastProjectPath = file->value("global/last_path", 0).toString();
        _lastProjectName = file->value("global/last_name", 0).toString();

        _editorScale = file->value("editor/scale", 1.0).toFloat();

        _timelineScale = file->value("stage/view_scale", 100.0).toFloat();
        _isAntialising = file->value("stage/antialising", true).toBool();

        _isScaleSet = file->value("global/SFTS", 0).toInt();

        _isTipsShow = file->value("tips/action", 0).toInt();
    }
}