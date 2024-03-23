#ifndef SQLITE_UTIL_H
#define SQLITE_UTIL_H

#include <QtSql/QSqlQuery>
#include <QStringList>

namespace Database{
    class SqliteUtil{
        public:
        static bool RunSql(const QStringList& orderList);
        static bool RunSql(QSqlQuery& query,const QString& order);
    };
}

#endif