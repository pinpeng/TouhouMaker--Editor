#include "dataSet/cacheAgent.h"

#define DATABASE_LIST_MAX_LENGTH 20

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
}

CacheAgent& CacheAgent::getInstance(){
    static CacheAgent agent;
    return agent;
}

Database CacheAgent::database(){
    return (*_curDatabase);
}

Database_info CacheAgent::databaseInfo(){
    return _curDatabase->info;
}

void CacheAgent::databaseInit(const QString& projectName,const QString& projectDir){
    // TODO... stage_id_top,stage_event_id_top,text_id_top没清，不确定要不要清
    stage_id_top = 100;

    hero_id_top = 100;
    enemy_id_top = 100;
    boss_id_top = 100;
    bullet_id_top = 100;

    effect_id_top = 100;
    audio_id_top = 100;
    image_id_top = 100;

    _databaseList.clear();
    _databaseList.append(Database(projectName, projectDir));
    _curDatabase = (--_databaseList.end());
}

// 更新数据库操作步骤
void CacheAgent::databaseUpdate(Database db){
    _databaseList.erase((_curDatabase + 1),_databaseList.end());
    _databaseList.append(db);
    ++_curDatabase;
    if(_databaseList.size() >= DATABASE_LIST_MAX_LENGTH){
        _databaseList.erase(_databaseList.begin(),(_databaseList.begin() + (_databaseList.size() - DATABASE_LIST_MAX_LENGTH)));
    }
}

void CacheAgent::databaseClean(){
    _databaseList.clear();
    _curDatabase = nullptr;
}

bool CacheAgent::databaseUndo(){
    if(_databaseList.begin() == _curDatabase){
        return false;
    }

    --_curDatabase;
    return true;
}

bool CacheAgent::databaseRedo(){
    if((_databaseList.end()-1 == _curDatabase)){
        return false;
    }

    ++_curDatabase;
    return true;
}

int CacheAgent::databaseLanSize(){
    return _curDatabase->info.language.length();
}








