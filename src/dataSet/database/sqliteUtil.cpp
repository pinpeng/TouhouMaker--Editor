#include "dataSet/database/sqliteUtil.h"
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>


namespace Database{
    bool SqliteUtil::RunSql(const QStringList& orderList){
        QSqlQuery query;
        if(!QSqlDatabase::database().transaction()){
            qWarning() << "set statement failed!";
        }
        qDebug() << "start set statement";
        for(const auto& order:orderList){
            qDebug() << "statement : "<< order;
            query.exec(order);
        }
        if(!QSqlDatabase::database().commit()){
            qCritical() << "commit failed! reason: " << QSqlDatabase::database().lastError();
            if(!QSqlDatabase::database().rollback()){
                qCritical() << "rollback failed! reason: " << QSqlDatabase::database().lastError();
            } 
            return false;
        }
        return true;
    }

    bool SqliteUtil::RunSql(QSqlQuery& query,const QString& order){
        qDebug() << "run order: "<<order;
        if(!query.exec(order)){
            qCritical() << "run order failed! reason: "<< QSqlDatabase::database().lastError();
            return false;
        }
        return true;
    }
}