#ifndef DATABASE_MAIN_H
#define DATABASE_MAIN_H

#include <QList>
#include <QString>

#include <QPixmap>

#include <QTextStream>
#include <QFile>

#include <QJsonDocument>
#include <QJsonArray>

class Window_editor_stage;

struct Database;

struct DB_UI_TITLE {
    DB_UI_TITLE();
};

struct DB_STAGE_EVENT {
    int id;
    int time;
    int type;
    QPixmap pixmap[4];

    QMap<QString, float> data;
    QMap<QString, QString> data_str;

    enum THMK_EVENT_TYPE {
        SET_BACKGROUND,
        SET_BGM,
        PLAY_SE,
        PLAY_EFFECT,
        CREATE_ENEMY,
        CREATE_ENEMY_TIME,
        PLAY_STORY,
        PLAY_STORY_TIME,
        BOSS_START,
        BOSS_END,
        BOSS_BULLET,
        BOSS_SPELL_CARD,
        CLS,
        GOTO,
        STAGE_CHANGE,
        POINT
    };

    DB_STAGE_EVENT();
    DB_STAGE_EVENT(int _id, int _time, int _type);

    void toJson(QMap<int, int> map_text,
                QMap<int, int> map_hero,
                QMap<int, int> map_enemy,
                QMap<int, int> map_boss,
                QMap<int, int> map_bullet[3],
                QMap<int, int> map_effect[3],
                QMap<int, int> map_audio[3],
                QMap<int, int> map_image[5],
                QJsonObject *jObj);

    void init(Database *db = nullptr);

    QStringList getDescribe(Database *db);
    void renderCode(Window_editor_stage *window, Database *db, QRectF _rect, float *_line, float ss);
    bool editCode(Window_editor_stage *window, Database *db, QRectF _rect, float *_line, float ss, float mx, float my);
    void wheelEvent(Window_editor_stage *window, Database *db, QRectF _rect, float *_line, float ss);
};

struct DB_STAGE {
    int id;
    QString name;
    float length;

    QList<DB_STAGE_EVENT> events;

    DB_STAGE();
    DB_STAGE(int _id, QString _name);
};


#endif // DATABASE_MAIN_H
