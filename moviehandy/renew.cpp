#include "renew.h"
#include "ui_renew.h"
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

renew::renew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::renew)
{
    ui->setupUi(this);

}

renew::~renew()
{
    delete ui;
}

void renew::init(QString i,QString t,QString p)
{
    user_id=i;
    user_type=t;
    user_password=p;
        if (Database::connect()) {
            QSqlDatabase db = Database::getDatabase();
            QSqlQuery query;


            int rowCount = 0;
            QString sql1= "SELECT COUNT(*) AS row_count FROM movie";
            query.exec(sql1);
            if (query.isActive() && query.next()) {
                rowCount = query.value("row_count").toInt();
                qDebug() << "行数：" << rowCount;
            } else {
                qDebug() << "查询失败：" << query.lastError().text();
            }

            // 初始化列数
            QString sql2 = "SELECT * FROM movie";
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
            list << "电影id" << "电影名称" << "电影类型" << "电影时长"<<"电影简介";
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

            // 输出表格内容
            /*for (int r = 0; r < rowCount; ++r) {
                for (int c = 0; c < columnCount; ++c) {
                    QTableWidgetItem* item = ui->movie->item(r, c);
                    qDebug() << "Row: " << r << ", Column: " << c << ", Value: " << item->text();
                }
            }*/

            Database::close();
        }

}

void renew::on_gotoin_clicked()
{
    ui->stack->setCurrentWidget(ui->Increase);
}

void renew::on_gotode_clicked()
{
    ui->stack->setCurrentWidget(ui->Decrease);
}

void renew::on_increase_clicked()
{
    QString m_id = ui->m_id->text();
    QString m_name = ui->m_name->document()->toPlainText();
    QString m_time = ui->m_time->text();
    QString m_type = ui->m_type->document()->toPlainText();
    QString m_brief = ui->m_brief->document()->toPlainText();
    QString flag= 0;
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QString movie = "SELECT* FROM movie WHERE m_id=:id";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(movie);
        sqlQuery.bindValue(":id", m_id);
        // 执行查询
        if (sqlQuery.exec()) {
            if (sqlQuery.next()) {
                QMessageBox::warning(this, "上架失败", "上架失败，请重新输入！");
                ui->m_id->clear();
                ui->m_name->clear();
                ui->m_time->clear();
                ui->m_type->clear();
                ui->m_brief->clear();
            }
            else {
                    // 向数据库movie表插入电影
                    QString insertQuery = "INSERT INTO movie (m_id, m_name, m_time,m_type,m_brief,flag) VALUES (:id, :name,:time,:type,:brief,1)";
                    QSqlQuery insertSqlQuery;
                    insertSqlQuery.prepare(insertQuery);
                    // 绑定参数
                    insertSqlQuery.bindValue(":id",m_id);
                    insertSqlQuery.bindValue(":name",m_name);
                    insertSqlQuery.bindValue(":time",m_time);
                    insertSqlQuery.bindValue(":type",m_type);
                    insertSqlQuery.bindValue(":brief",m_brief);
                    insertSqlQuery.bindValue(":flag",flag);
                    // 执行插入
                    if (insertSqlQuery.exec()) {
                        QMessageBox::information(this, "上架成功", "上架成功！");
                        ui->stack->setCurrentWidget(ui->Decrease);
                    } else {
                        QMessageBox::critical(this, "错误", "上架失败：" + insertSqlQuery.lastError().text());
                    }
                }

        } else {
            QMessageBox::critical(this, "错误", "数据库查询错误：" + sqlQuery.lastError().text());
        }
    Database::close();
    }

}



void renew::on_decrease_clicked()
{
    int movieId = ui->lineEdit->text().toInt();
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QString movie = "SELECT* FROM movie WHERE m_id=:id";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(movie);
        sqlQuery.bindValue(":id", movieId);
        // 执行查询
        if (sqlQuery.exec()) {
            if (sqlQuery.next()) {
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE movie SET flag = 0 WHERE m_id = :movieId");
                    updateQuery.bindValue(":movieId", movieId);
                    if (!updateQuery.exec()) {
                        qDebug() << "更新失败：" << updateQuery.lastError().text();
                                                    return;
                    }
                    QMessageBox::information(this, "下架成功", "下架成功！");
                    qDebug() << "电影 ID: " << movieId << " 下架成功";
            }
            else {
                    qDebug() << "查询失败：" << sqlQuery.lastError().text();
                                                return;
                }

        } else {
            QMessageBox::critical(this, "错误", "数据库查询错误：" + sqlQuery.lastError().text());
        }
    Database::close();
    }

}

void renew::on_refresh_clicked()
{
    ui->movie->clear();

    ui->movie->clearContents();
    ui->movie->setRowCount(0);
    ui->movie->setColumnCount(0);

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery query;


        int rowCount = 0;
        QString sql1= "SELECT COUNT(*) AS row_count FROM movie";
        query.exec(sql1);
        if (query.isActive() && query.next()) {
            rowCount = query.value("row_count").toInt();
            qDebug() << "行数：" << rowCount;
        } else {
            qDebug() << "查询失败：" << query.lastError().text();
        }

        // 初始化列数
        QString sql2 = "SELECT * FROM movie";
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
        list << "电影id" << "电影名称" << "电影类型" << "电影时长"<<"电影简介";
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

        // 输出表格内容
        /*for (int r = 0; r < rowCount; ++r) {
            for (int c = 0; c < columnCount; ++c) {
                QTableWidgetItem* item = ui->movie->item(r, c);
                qDebug() << "Row: " << r << ", Column: " << c << ", Value: " << item->text();
            }
        }*/

        Database::close();
    }

}

