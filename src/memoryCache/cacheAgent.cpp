#include "memoryCache/cacheAgent.h"
#include "toolkit/fileoperator.h"

#define DATABASE_LIST_MAX_LENGTH 20

CacheAgent::CacheAgent()
:setting(ToolKit::FileOperator::GetSubModulePath(ToolKit::FileModule::SETTING)+"editorSetting.ini")
{
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
    return _databaseList[_curDbIndex];
}

Database_info CacheAgent::databaseInfo(){
    return _databaseList[_curDbIndex].info;
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
    _databaseList.push_back(Database(projectName, projectDir));
    _curDbIndex = 0;
}

// 更新缓存操作步骤
void CacheAgent::databaseUpdate(Database db){
    if(_curDbIndex < _databaseList.size() - 1){
        _databaseList.erase(_databaseList.begin()+_curDbIndex + 1,_databaseList.end());
    }

    _databaseList.push_back(db);
    ++_curDbIndex;
    if(_databaseList.size() >= DATABASE_LIST_MAX_LENGTH){
        _databaseList.erase(_databaseList.begin(),(_databaseList.begin() + (_databaseList.size() - DATABASE_LIST_MAX_LENGTH)));
    }
}

void CacheAgent::databaseClean(){
    _databaseList.clear();
    _curDbIndex = -1;
}

bool CacheAgent::databaseUndo(){
    if(_curDbIndex == 0){
        return false;
    }

    --_curDbIndex;
    return true;
}

bool CacheAgent::databaseRedo(){
    if(_curDbIndex == _databaseList.size() - 1){
        return false;
    }

    ++_curDbIndex;
    return true;
}

int CacheAgent::databaseLanSize(){
    return _databaseList[_curDbIndex].info.language.length();
}

bool CacheAgent::saveToDatabase(){

}

bool CacheAgent::initFromDatabase(){

}