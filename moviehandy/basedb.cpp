#include "basedb.h"
#include<QSqlDatabase>

basedb::basedb()
{
    //加载sqlite数据库驱动
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    //生成数据库文件
    mydb.setDatabaseName("form.db");
    //开启数据库
    mydb.open();
}

basedb::~basedb()
{

}
