#include "admininfo.h"
#include "ui_admininfo.h"
#include "database.h"
#include<QApplication>
#include<QDebug>
#include<QSqlDatabase>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QSqlQuery>
#include<QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSpinBox>
#include <QCheckBox>


admininfo::admininfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admininfo)
{
    ui->setupUi(this);

}

admininfo::~admininfo()
{
    delete ui;
}

void admininfo::init(QString i,QString t,QString p)
{
    user_id=i;
    user_type=t;
    user_password=p;

    // 将 userId 值追加到 QTextBrowser
    ui->textBrowser->setText(user_id);

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery query;


        int rowCount = 0;
        QString sql1= "SELECT COUNT(*) AS row_count FROM user";
        query.exec(sql1);
        if (query.isActive() && query.next()) {
            rowCount = query.value("row_count").toInt();
            qDebug() << "行数：" << rowCount;
        } else {
            qDebug() << "查询失败：" << query.lastError().text();
        }

        // 初始化列数
        QString sql2 = "SELECT * FROM user";
        query.exec(sql2);
        int columnCount=1;
        if (query.isActive() && query.next()) {
            QSqlRecord record = query.record();
            columnCount = record.count();
            qDebug() << "列数：" << columnCount;
        } else {
            qDebug() << "查询失败：" << query.lastError().text();
        }


        //设置行数和列数
        // QTableWidget* tableWidget = new QTableWidget();
        ui->movie->setRowCount(rowCount);
        ui->movie->setColumnCount(columnCount);

        //自动调整宽度
        QHeaderView* widthlist = ui->movie->horizontalHeader();               //创建列宽list
        ui->movie->horizontalHeader()->setStretchLastSection(true);
        widthlist->setStretchLastSection(true);
        // 最后一栏自适应宽度
        QStringList list;
        //将表头写入表格                                                     // 创建列表头list
        list << "用户id" << "用户密码" << "用户类型" << "用户活跃度";
        ui->movie->setHorizontalHeaderLabels(list);
        // 填充表格数据

        int row = 0;
        while (query.next()) {
            for (int column = 0; column < columnCount; ++column) {
                QTableWidgetItem* item = new QTableWidgetItem(query.value(column).toString());
                ui->movie->setItem(row, column, item);
            }
            ++row;
        }
        ui->movie->verticalHeader()->setVisible(false); //隐藏垂直表头

        Database::close();
    }
}

void admininfo::on_do_manage_clicked()
{
    ui->stack->setCurrentWidget(ui->manage_page);
    int userid=ui->lineEdit->text().toInt();

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QString userquery = "SELECT u_id,u_pass,u_act FROM user WHERE u_id =:uid";
        QSqlQuery query;
        query.prepare(userquery);
        query.bindValue(":uid", userid);
        query.exec();
        if (query.exec()) {
            if (query.next()) {
                int u_id = query.value(0).toInt();
                ui->user_id->setText(QString::number(u_id));
                int u_pass = query.value(1).toInt();
                ui->user_pass->setText(QString::number(u_pass));
                int u_act = query.value(2).toInt();
                ui->user_act->setText(QString::number(u_act));
            }
        } else {
            // 查询执行失败
            QMessageBox::critical(this, "错误", "user表查询错误" + query.lastError().text());
            // 处理查询失败的情况
        }
        Database::close();
    }
}

void admininfo::on_do_update_clicked()
{
    QString u_id = ui->lineEdit->text();
    QString u_act = ui->user_act->text();
    QString u_pass = ui->user_pass->text();

    if (Database::connect()) {

        QSqlDatabase db = Database::getDatabase();

        QString updateQuery = "UPDATE user SET u_pass=:pass,u_act =:active WHERE u_id = :userId";
        QSqlQuery updateSqlQuery;
        updateSqlQuery.prepare(updateQuery);
        // 绑定参数
        updateSqlQuery.bindValue(":userId", u_id);
        updateSqlQuery.bindValue(":active", u_act);
        updateSqlQuery.bindValue(":pass", u_pass);
        if(updateSqlQuery.exec()){
            QMessageBox::information(this, "更新成功", "更新成功！");
            ui->lineEdit->clear();
            ui->stack->setCurrentWidget(ui->info_page);
        } else {
            QMessageBox::critical(this, "错误", "user表更新失败：" + updateSqlQuery.lastError().text());
        }
    }
    Database::close();
}

void admininfo::on_do_delete_clicked()
{
    QString u_id = ui->lineEdit->text();
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QString deleteQuery = "DELETE FROM user WHERE u_id = :userId";
        QSqlQuery deleteSqlQuery;
        deleteSqlQuery.prepare(deleteQuery);
        // 绑定参数
        deleteSqlQuery.bindValue(":userId", u_id);
        if(deleteSqlQuery.exec()){
            QMessageBox::information(this, "删除成功", "删除成功！");
            ui->lineEdit->clear();
            ui->stack->setCurrentWidget(ui->info_page);
        } else {
            QMessageBox::critical(this, "错误", "user表删除失败：" + deleteSqlQuery.lastError().text());
        }
    }
    Database::close();
}

void admininfo::on_back_clicked()
{
    ui->lineEdit->clear();
    ui->stack->setCurrentWidget(ui->info_page);
}


void admininfo::on_refresh_clicked()
{
     ui->movie->clear();
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery query;


        int rowCount = 0;
        QString sql1= "SELECT COUNT(*) AS row_count FROM user";
        query.exec(sql1);
        if (query.isActive() && query.next()) {
            rowCount = query.value("row_count").toInt();
            qDebug() << "行数：" << rowCount;
        } else {
            qDebug() << "查询失败：" << query.lastError().text();
        }

        // 初始化列数
        QString sql2 = "SELECT * FROM user";
        query.exec(sql2);
        int columnCount=1;
        if (query.isActive() && query.next()) {
            QSqlRecord record = query.record();
            columnCount = record.count();
            qDebug() << "列数：" << columnCount;
        } else {
            qDebug() << "查询失败：" << query.lastError().text();
        }


        //设置行数和列数
        // QTableWidget* tableWidget = new QTableWidget();
        ui->movie->setRowCount(rowCount);
        ui->movie->setColumnCount(columnCount);

        //自动调整宽度
        QHeaderView* widthlist = ui->movie->horizontalHeader();               //创建列宽list
        ui->movie->horizontalHeader()->setStretchLastSection(true);
        widthlist->setStretchLastSection(true);
        // 最后一栏自适应宽度
        QStringList list;
        //将表头写入表格                                                     // 创建列表头list
        list << "用户id" << "用户密码" << "用户类型" << "用户活跃度";
        ui->movie->setHorizontalHeaderLabels(list);
        // 填充表格数据

        int row = 0;
        while (query.next()) {
            for (int column = 0; column < columnCount; ++column) {
                QTableWidgetItem* item = new QTableWidgetItem(query.value(column).toString());
                ui->movie->setItem(row, column, item);
            }
            ++row;
        }
    Database::close();
    }
}

