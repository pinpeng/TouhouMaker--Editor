#ifndef DB_AGENT_H
#define DB_AGENT_H

#include "dataSet/database/sqliteUtil.h"

class DatabaseAgent{
    public:
    static DatabaseAgent& GetInstance();
    
    private:
    DatabaseAgent();
};

#endif