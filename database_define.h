#ifndef DATABASE_DEFINE_H
#define DATABASE_DEFINE_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QRectF>
#include <QJsonDocument>
#include <QJsonArray>


////////////////////////////////

struct Database;

class Window_editor_menubar_bullet_edit;

class Window_editor_menubar_effect_edit;

class Window_editor_menubar_hero_edit1;


struct DB_text {
    int __id;
    QList<QString> __text;

    DB_text();
    DB_text(int _id, QString _text);

    QString getText(int _lan);
    void setText(int _lan, QString _text);
};

struct DB_hero_bullet {
    QMap<QString, float> data;

    DB_hero_bullet();

};

struct DB_hero_skill {
    int name;
    QMap<QString, float> data;

    DB_hero_skill();
    DB_hero_skill(Database *db, QString _name);
};

struct DB_hero {
    int __id;
    int name;

    DB_hero_bullet bullet[2];
    int bullet_type;
    DB_hero_skill skill[2];
    int skill_type;

    int image_id[6];
    // idle, lmove, rmove, deco, slowdown, preview

    DB_hero();
    DB_hero(Database *db, int _id, QString _name);
};

struct DB_enemy {
    int __id;
    QString name;
    QMap<QString, float> data;
    QMap<QString, QString> data_str;

    int image_id;

    DB_enemy();
    DB_enemy(int _id, QString _name);

    void toJson(QMap<int, int> map_text,
                QMap<int, int> map_hero,
                QMap<int, int> map_enemy,
                QMap<int, int> map_boss,
                QMap<int, int> map_bullet[3],
                QMap<int, int> map_effect[3],
                QMap<int, int> map_audio[3],
                QMap<int, int> map_image[5],
                QJsonObject *jObj);

    void init();
    void updateData();

    void renderCode(Window_editor_menubar_hero_edit1 *window, Database *db, QRectF _rect, float *_line);
    bool editCode(Window_editor_menubar_hero_edit1 *window, Database *db, QRectF _rect, float *_line, float mx, float my);
    void wheelEvent(Window_editor_menubar_hero_edit1 *window, Database *db, QRectF _rect, float *_line);
};

struct DB_boss {
    int __id;
    int name;
    int image_id[3];

    DB_boss();
    DB_boss(Database *db, int _id, QString _name);
};

struct DB_bullet {
    int __id;
    QString name;
    QMap<QString, float> data;
    QMap<QString, QString> data_str;

    int image_id;

    DB_bullet();
    DB_bullet(int _id, QString _name);

    void toJson(int _group,
                QMap<int, int> map_text,
                QMap<int, int> map_hero,
                QMap<int, int> map_enemy,
                QMap<int, int> map_boss,
                QMap<int, int> map_bullet[3],
                QMap<int, int> map_effect[3],
                QMap<int, int> map_audio[3],
                QMap<int, int> map_image[5],
                QJsonObject *jObj);

    void init();
    void updateData();

    void renderCode(Window_editor_menubar_bullet_edit *window, Database *db, QRectF _rect, float *_line, int _group);
    bool editCode(Window_editor_menubar_bullet_edit *window, Database *db, QRectF _rect, float *_line, float mx, float my, int _group);
    void wheelEvent(Window_editor_menubar_bullet_edit *window, Database *db, QRectF _rect, float *_line);
};

struct DB_effect {
    int __id;
    QString name;
    QMap<QString, float> data;

    DB_effect();
    DB_effect(int _id, QString _name);

    void init();

    void renderCode(Window_editor_menubar_effect_edit *window, Database *db, QRectF _rect, float *_line);
    bool editCode(Window_editor_menubar_effect_edit *window, Database *db, QRectF _rect, float *_line, float mx, float my);
    void wheelEvent(Window_editor_menubar_effect_edit *window, Database *db, QRectF _rect, float *_line);
};

struct DB_audio { // bgm or se, .ogg
    int __id;
    QString name;
    int state; // 0 = not saved, 1 = .ogg saved

    DB_audio();
    DB_audio(int _id, QString _name);
};


struct DB_image { // background, etc, .png
    int __id;
    QString name;
    int state; // 0 = not saved, 1 = .png saved, 2 = .gif saved
    int editTimer;

    DB_image();
    DB_image(int _id, QString _name);
};


#endif // DATABASE_DEFINE_H





















