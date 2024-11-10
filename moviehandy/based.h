//basedb.h

#ifndef BASEDB_H
#define BASEDB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
class basedb
{
public:
    //数据库对象
    QSqlDatabase db;
    basedb();
    ~basedb();
};

#endif // BASEDB_H
