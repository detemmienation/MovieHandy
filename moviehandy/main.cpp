#include "mainwindow.h"
#include "login.h"

#include<QApplication>
#include<QDebug>
#include<QSqlDatabase>

#include<QSqlQuery>
#include<QSqlError>

void create_table();
bool open_database();

int main(int argc, char *argv[])
{
    open_database();
    // create_table();
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}

void create_table()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("whuhyse002.mysql.polardb.rds.aliyuncs.com");
    mydb.setPort(3306);
    mydb.setDatabaseName("user01db");
    mydb.setUserName("user01");
    mydb.setPassword("2020300004001ljy_");
    mydb.open();
    if (!mydb.open()) {
        qDebug() << "Failed to open the database";
        return;
    }
    else
    {
        QSqlQuery sql_query(mydb);
        QString  sqlcreate = QString("CREATE TABLE IF NOT EXISTS Address(id int primary key, name varchar(255))"
                                    );
        sql_query.exec(sqlcreate);
        if (!sql_query.exec()) {
            qDebug() << "Failed to create table!"<< sql_query.lastError().text();
            return;
        }
        else
        {
            qDebug() << "Table created!";
        }
        mydb.close();
    }
}

bool open_database()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("whuhyse002.mysql.polardb.rds.aliyuncs.com");
    mydb.setPort(3306);
    mydb.setDatabaseName("user01db");
    mydb.setUserName("user01");
    mydb.setPassword("2020300004001ljy_");

    if(mydb.open())
    {
        qDebug()<<"open success";
        return true;
    }
    else
    {
        qDebug()<<"open failed";
        return false;
    }
}

