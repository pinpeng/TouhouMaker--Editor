#ifndef SETTING_H
#define SETTING_H

#include <QList>
#include <QString>
#include <QSettings>
#include <QSharedPointer>

enum ThemeColor{
    INVALID = 255,
    DEFAULT = 0,
    GRAY = 1,
    DARK = 2,
    CUSTOM = 3                  // 用户自定义背景色
};

class EditorSetting
{
    public:
    EditorSetting();
    void read();
    void save();

    public:  
    ThemeColor themeColor();
    bool setThemeColor(ThemeColor color);

    QString lastProjectPath();
    QString lastProjectName();
    bool setLastProjectPosition(const QString& path,const QString& name);

    float editorScale();
    bool setEditorScale(float scale);

    float timelineScale();
    bool setTimelineScale(float scale);

    bool stageAntialising();
    bool setStageAntialising(bool flag);

    int tipsAction();
    bool setTipsAction(int action);

    ThemeColor _themeColor = ThemeColor::INVALID;     // 0 = default, 1 = gray, 2 = dark, 3 = custom

    QString _lastProjectPath = "";

    QString _lastProjectName;

    float _editorScale;         // 0.75 -- 1.5

    float _timeLineScale;       // 50 -- 200

    bool _stageAntialising;

    int _tipsAction;            // 0 = all, 1 = half, 2 = close

    QSharedPointer<QSettings> _iniFile;
};

#endif // SETTING_H
