#include "database_main.h"

#include <QDir>

#include "dataSet/cacheAgent.h"
#include "dataSet/memoryCache/database.h"

DB_UI_TITLE::DB_UI_TITLE()
{

}


DB_STAGE_EVENT::DB_STAGE_EVENT()
{
    data["enable"] = 0;
}

DB_STAGE_EVENT::DB_STAGE_EVENT(int _id, int _time, int _type)
{
    data["enable"] = 1;
    id = _id;
    time = _time;
    type = _type;
    init();
}

DB_STAGE::DB_STAGE()
{

}

DB_STAGE::DB_STAGE(int _id, QString _name)
{
    id = _id;
    name = _name;
    length = 18000;

    events.append(DB_STAGE_EVENT(++CacheAgent::getInstance().stage_event_id_top, 0, 0));
    events.append(DB_STAGE_EVENT(++CacheAgent::getInstance().stage_event_id_top, 30, 1));
}
