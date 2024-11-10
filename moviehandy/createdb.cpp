#include "createdb.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>


createdb::createdb()
{
    QSqlQuery sql_query;
    QString create_table = "create table if not exists score (id INTEGER PRIMARY KEY,name TEXT NOT NULL,uclass TEXT,math INTEGER,chinese INTEGER,English INTEGER,physics INTEGER,chemics INTEGER,biology INTEGER)";
    sql_query.prepare(create_table);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}
