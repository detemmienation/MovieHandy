#include "userinfo.h"
#include "ui_userinfo.h"
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

userinfo::userinfo(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::userinfo)
{
    ui->setupUi(this);

}

userinfo::~userinfo()
{
    delete ui;
}

void userinfo::init(QString i,QString t,QString p)
{
    user_id = i;
    user_type = t;
    user_password = p;


    // Append the userId value to the QTextBrowser
    //显示userid
    ui->textBrowser->setText(user_id);

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QString query = "SELECT u_act FROM user WHERE u_id = :id";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.bindValue(":id", user_id);

        if (sqlQuery.exec() && sqlQuery.next()) {
                //显示useractive
            QString user_active = sqlQuery.value("u_act").toString();
            ui->textBrowser_3->setText(user_active);
        }
        Database::close();
    }


}


//补全订单查询操作
void userinfo::on_buy_search_clicked()
{
    int uid=user_id.toInt();
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QStringList list;
        list<<"用户id"<<"电影id"<<"日期"<<"时间段"<<"座位号";
        QString query="select u_id,m_id,date,time,seat from orders where u_id= :uid";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.bindValue(":uid", uid);

        if(sqlQuery.exec())
        {
            ui->tableWidget_2->clearContents();
            ui->tableWidget_2->setRowCount(0);
            ui->tableWidget_2->setColumnCount(list.size());
            ui->tableWidget_2->setHorizontalHeaderLabels(list);

            while(sqlQuery.next())
            {
                int rowCount = ui->tableWidget->rowCount();

                ui->tableWidget_2->insertRow(rowCount);

                QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                            sqlQuery.value(0).toString());
                ui->tableWidget_2->setItem(rowCount,0, columnItem0);

                QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                            sqlQuery.value(1).toString());
                ui->tableWidget_2->setItem(rowCount,1, columnItem1);

                QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                            sqlQuery.value(2).toString());
                ui->tableWidget_2->setItem(rowCount,2, columnItem2);

                QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                            sqlQuery.value(3).toString());
                ui->tableWidget_2->setItem(rowCount,3, columnItem3);

                QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                            sqlQuery.value(4).toString());
                ui->tableWidget_2->setItem(rowCount,4, columnItem4);

//                ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏水平表头
                ui->tableWidget_2->verticalHeader()->setVisible(false); //隐藏垂直表头
                ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            }
        } else {
            QMessageBox::critical(this, "错误", "orders表查询错误：" + sqlQuery.lastError().text());
        }
        Database::close();
    }

    ui->stack->setCurrentWidget(ui->buy_result);

}

//补全投票查询操作
void userinfo::on_vote_search_clicked()
{
    ui->stack->setCurrentWidget(ui->vote_result);

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery query;
        int rowCount = 0;

        QString sql1 = "SELECT COUNT(*) AS row_count FROM vote WHERE u_id = :id";
        query.prepare(sql1);
        query.bindValue(":id", user_id.toInt());

        if (query.exec() && query.next()) {
            rowCount = query.value("row_count").toInt();
            qDebug() << "userid：" << user_id.toInt();
            qDebug() << "行数：" << rowCount;
        } else {
            qDebug() << "查询失败：" << query.lastError().text();
        }

        // 初始化列数
        QString sql2 = "SELECT * FROM vote";
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
        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setColumnCount(columnCount);

        //自动调整宽度
        QHeaderView* widthlist = ui->tableWidget->horizontalHeader();               //创建列宽list
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        widthlist->setStretchLastSection(true);
        // 最后一栏自适应宽度
        QStringList list;
        //将表头写入表格                                                     // 创建列表头list
        list << "用户id" << "电影日期" << "电影时间" << "电影id";
        ui->tableWidget->setHorizontalHeaderLabels(list);
        // 填充表格数据

        int row = 0;
        while (query.next()) {
            int u_id = query.value("u_id").toInt();
            if (u_id == user_id.toInt()) { // 只显示user_id 为 3 的条目
            for (int column = 0; column < columnCount; ++column) {
                QTableWidgetItem* item = new QTableWidgetItem(query.value(column).toString());
                ui->tableWidget->setItem(row, column, item);
            }
            ++row;
            }
        ui->tableWidget->verticalHeader()->setVisible(false); //隐藏垂直表头
        }

        Database::close();
    }

}

void userinfo::on_back_toinfo1_clicked()
{
    ui->stack->setCurrentWidget(ui->info_page);
}

void userinfo::on_back_toinfo2_clicked()
{
    ui->stack->setCurrentWidget(ui->info_page);
}

