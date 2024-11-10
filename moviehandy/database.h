#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database {
public:
    static bool connect();
    static void close();
    static QSqlDatabase getDatabase();

private:
    static QSqlDatabase database;
};

#endif // DATABASE_H
