#ifndef DB_AGENT_H
#define DB_AGENT_H

class DatabaseAgent{
    public:
    static DatabaseAgent& GetInstance();
    private:
    DatabaseAgent();
};

#endif