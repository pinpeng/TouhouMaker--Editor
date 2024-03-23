#ifndef DATABASE_INFO_H
#define DATABASE_INFO_H

#include <QList>

struct Database_info {
    Database_info();
    void clear();
    void init();

    QList<QString> language;

    QString projectName;
    QString projectPosition;

};

#endif // DATABASE_INFO_H
