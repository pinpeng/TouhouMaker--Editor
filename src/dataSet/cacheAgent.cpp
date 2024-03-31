#include "dataSet/cacheAgent.h"

CacheAgent::CacheAgent(){
    stage_id_top = 100;
    stage_event_id_top = 100;

    text_id_top = 100;
    hero_id_top = 100;
    enemy_id_top = 100;
    boss_id_top = 100;
    bullet_id_top = 100;

    effect_id_top = 100;
    audio_id_top = 100;
    image_id_top = 100;

    database_list_max_size = 20;
}

CacheAgent& CacheAgent::getInstance(){
    static CacheAgent agent;
    return agent;
}

Database CacheAgent::database() {
    return database_list.top();
}

Database_info CacheAgent::databaseInfo()
{
    return database_list.top().info;
}

void CacheAgent::databaseInit(QString _name, QString _position) {
    // TODO... stage_id_top,stage_event_id_top,text_id_top没清，不确定要不要清
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

void CacheAgent::databaseUpdate(Database db) {
    if(database_list_last.size()) database_list_last.clear();
    database_list.push(db);
    while(database_list.size() >= database_list_max_size) {
        database_list.pop_front();
    }
}

void CacheAgent::databaseClean()
{
    database_list.clear();
    database_list_last.clear();
}

bool CacheAgent::databaseUndo() {
    if(database_list.size() > 1) {
        database_list_last.push(database_list.top());
        database_list.pop();
        return true;
    } else return false;
}

bool CacheAgent::databaseRedo() {
    if(database_list_last.size()) {
        database_list.push(database_list_last.top());
        database_list_last.pop();
        return true;
    } else return false;
}

int CacheAgent::databaseLanSize()
{
    return database_list.top().info.language.length();
}








