#ifndef SETTING_H
#define SETTING_H

#include <QList>
#include <QString>

#include <QSettings>

struct Setting
{
    int global_color_group; // 0 = default, 1 = gray, 2 = dark, 3 = custom
    QString global_last_path;
    QString global_last_name;

    float editor_scale; // 0.75 -- 1.5

    float timeline_scale; // 50 -- 200
    bool stage_antialising;

    int tips_action; // 0 = all, 1 = half, 2 = close


    Setting() { read(); }

    void read() {
        QSettings *file = new QSettings("setting.ini", QSettings::IniFormat);

        global_color_group = file->value("global/color_group", 0).toInt();
        global_last_path = file->value("global/last_path", 0).toString();
        global_last_name = file->value("global/last_name", 0).toString();

        editor_scale = file->value("editor/scale", 1.0).toFloat();

        timeline_scale = file->value("stage/view_scale", 100.0).toFloat();
        stage_antialising = file->value("stage/antialising", true).toBool();

        tips_action = file->value("tips/action", 0).toInt();

        delete file;
    }

    void save() {
        QSettings *file = new QSettings("setting.ini", QSettings::IniFormat);
        file->setValue("global/color_group", global_color_group);
        file->setValue("global/last_path", global_last_path);
        file->setValue("global/last_name", global_last_name);

        file->setValue("editor/scale", editor_scale);

        file->setValue("stage/view_scale", timeline_scale);
        file->setValue("stage/antialising", stage_antialising);

        file->setValue("tips/action", tips_action);
        delete file;
    }
};

#endif // SETTING_H
