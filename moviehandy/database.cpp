#include "database.h"

QSqlDatabase Database::database;

bool Database::connect()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("whuhyse002.mysql.polardb.rds.aliyuncs.com");
    database.setPort(3306);
    database.setDatabaseName("user01db");
    database.setUserName("user01");
    database.setPassword("2020300004001ljy_");

    return database.open();
}

void Database::close()
{
    database.close();
}

QSqlDatabase Database::getDatabase()
{
    return database;
}

