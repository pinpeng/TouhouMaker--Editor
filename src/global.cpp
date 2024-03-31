#include "global.h"

EditorSetting Global::setting = EditorSetting();

int Global::stage_id_top = 100;
int Global::stage_event_id_top = 100;

int Global::text_id_top = 100;
int Global::hero_id_top = 100;
int Global::enemy_id_top = 100;
int Global::boss_id_top = 100;
int Global::bullet_id_top = 100;

int Global::effect_id_top = 100;
int Global::audio_id_top = 100;
int Global::image_id_top = 100;

int                  Global::database_list_max_size = 20;
QStack<Database>     Global::database_list          = QStack<Database>();
QStack<Database>     Global::database_list_last     = QStack<Database>();

QMap<QString, sprite_buff> Global::sprite_buffer        = QMap<QString, sprite_buff>();

Database Global::database() {
    return database_list.top();
}

Database_info Global::databaseInfo()
{
    return database_list.top().info;
}

void Global::databaseInit(QString _name, QString _position) {
    stage_id_top = 100;

    hero_id_top = 100;
    enemy_id_top = 100;
    boss_id_top = 100;
    bullet_id_top = 100;

    effect_id_top = 100;
    audio_id_top = 100;
    image_id_top = 100;

    database_list.clear();
    database_list.push(Database(_name, _position));
}

void Global::databaseUpdate(Database db) {
    if(database_list_last.size()) database_list_last.clear();
    database_list.push(db);
    while(database_list.size() >= database_list_max_size) {
        database_list.pop_front();
    }
}

void Global::databaseClean()
{
    database_list.clear();
    database_list_last.clear();
}

bool Global::databaseUndo() {
    if(database_list.size() > 1) {
        database_list_last.push(database_list.top());
        database_list.pop();
        return true;
    } else return false;
}

bool Global::databaseRedo() {
    if(database_list_last.size()) {
        database_list.push(database_list_last.top());
        database_list_last.pop();
        return true;
    } else return false;
}

int Global::databaseLanSize()
{
    return database_list.top().info.language.length();
}








