#include "dataSet/editorSetting.h"
#include <QString>
#include <QFile>
#include <QTextCodec>
#include "toolkit/fileoperator.h"
#include "draw.h"

EditorSetting::EditorSetting(){
    QString fileName = ToolKit::FileOperator::GetSubModulePath(ToolKit::FileModule::SETTING) + "setting.ini";
    _iniFile = QSharedPointer<QSettings>::create(fileName,QSettings::IniFormat);
    _iniFile->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName)){
        read();
    }
    else{
        // 读取默认参数
        read();
        // 设置到文件当中
        save();
    }
}

void EditorSetting::read(){
    _themeColor = static_cast<ThemeColor>(_iniFile->value("global/color_group", 0).toInt());
    _lastProjectPath = _iniFile->value("global/last_path", 0).toString();
    _lastProjectName = _iniFile->value("global/last_name", 0).toString();

    _editorScale = _iniFile->value("editor/scale", 1.0).toFloat();

    _timeLineScale = _iniFile->value("stage/view_scale", 100.0).toFloat();
    _stageAntialising = _iniFile->value("stage/antialising", true).toBool();

    _tipsAction = _iniFile->value("tips/action", 0).toInt();
}

void EditorSetting::save(){
    _iniFile->setValue("global/color_group", _themeColor);
    _iniFile->setValue("global/last_path", _lastProjectPath);
    _iniFile->setValue("global/last_name", _lastProjectName);

    _iniFile->setValue("editor/scale", _editorScale);

    _iniFile->setValue("stage/view_scale", _timeLineScale);
    _iniFile->setValue("stage/antialising", _stageAntialising);

    _iniFile->setValue("tips/action", _tipsAction);
    _iniFile->sync();
}

ThemeColor EditorSetting::themeColor(){
    return _themeColor;
}

bool EditorSetting::setThemeColor(ThemeColor color){
    if(_themeColor != color){
        _themeColor = color;
        // save();
        Col::setThemeColor(color);
    }
    return true;
}

QString EditorSetting::lastProjectPath(){
    return _lastProjectPath;
}

QString EditorSetting::lastProjectName(){
    return _lastProjectName;
}

bool EditorSetting::setLastProjectPosition(const QString& path,const QString& name){
//    bool isChange = false;
    if(_lastProjectPath != path){
        _lastProjectPath = path;
//        isChange = true;
    }
    if(_lastProjectName != name){
        _lastProjectName = name;
//        isChange = true;
    }
    // if(isChange){
        // save();
    // }
    return true;
}

float EditorSetting::editorScale(){
    return _editorScale;
}

bool EditorSetting::setEditorScale(float scale){
    // TODO... 后续考虑浮点数误差
    if(_editorScale != scale){
        _editorScale = scale;
        // save();
    }
    return true;
}

float EditorSetting::timelineScale(){
    return _timeLineScale;
}

bool EditorSetting::setTimelineScale(float scale){
    if(_timeLineScale != scale){
        _timeLineScale = scale;
    }
    return true;
}

bool EditorSetting::stageAntialising(){
    return _stageAntialising;
}

bool EditorSetting::setStageAntialising(bool flag){
    if(_stageAntialising != flag){
        _stageAntialising = flag;
    }
    return true;
}

int EditorSetting::tipsAction(){
    return _tipsAction;
}

bool EditorSetting::setTipsAction(int action){
    if(_tipsAction != action){
        _tipsAction = action;
    }
    return true;
}
