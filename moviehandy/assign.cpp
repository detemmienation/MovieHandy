#include "assign.h"
#include "ui_assign.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include "database.h"
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>

assign::assign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::assign)
{
    ui->setupUi(this);

}

assign::~assign()
{
    delete ui;
}

void assign::init(QString i,QString t,QString p)
{
    user_id=i;
    user_type=t;
    user_password=p;
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
}

void assign::on_date_select_clicked()
{
    QDate date=ui->dateEdit->date();
    ui->dateEdit->setReadOnly(true);

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QStringList list;
        list<<"电影id"<<"日期"<<"9：00-11：00该电影投票数"<<"13：00-15：00该电影投票数"<<"15：00-17：00该电影投票数"<<"17：00-19：00该电影投票数"<<"19：00-21：00该电影投票数"<<"21：00-23：00该电影投票数";
        QString query="select m_id,date,am9,pm1,pm3,pm5,pm7,pm9 from vote_result where date= :date";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.bindValue(":date", QVariant(date));

        if(sqlQuery.exec())
        {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(list.size());
            ui->tableWidget->setHorizontalHeaderLabels(list);

            while(sqlQuery.next())
            {
                int rowCount = ui->tableWidget->rowCount();

                ui->tableWidget->insertRow(rowCount);

                QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                            sqlQuery.value(0).toString());
                ui->tableWidget->setItem(rowCount,0, columnItem0);

                QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                            sqlQuery.value(1).toString());
                ui->tableWidget->setItem(rowCount,1, columnItem1);

                QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                            sqlQuery.value(2).toString());
                ui->tableWidget->setItem(rowCount,2, columnItem2);

                QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                            sqlQuery.value(3).toString());
                ui->tableWidget->setItem(rowCount,3, columnItem3);

                QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                            sqlQuery.value(4).toString());
                ui->tableWidget->setItem(rowCount,4, columnItem4);

                QTableWidgetItem *columnItem5 = new QTableWidgetItem(
                            sqlQuery.value(5).toString());
                ui->tableWidget->setItem(rowCount,5, columnItem5);

                QTableWidgetItem *columnItem6 = new QTableWidgetItem(
                            sqlQuery.value(6).toString());
                ui->tableWidget->setItem(rowCount,6, columnItem6);

                QTableWidgetItem *columnItem7 = new QTableWidgetItem(
                            sqlQuery.value(7).toString());
                ui->tableWidget->setItem(rowCount,7, columnItem7);

//                ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏水平表头
                ui->tableWidget->verticalHeader()->setVisible(false); //隐藏垂直表头
                ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            }
        } else {
            QMessageBox::critical(this, "错误", "数据库查询错误：" + sqlQuery.lastError().text());
        }
        Database::close();
    }
}


void assign::on_do_assign_clicked()
{
    int movie1=ui->movie1->text().toInt();
    int movie2=ui->movie2->text().toInt();
    int movie3=ui->movie3->text().toInt();
    int movie4=ui->movie4->text().toInt();
    int movie5=ui->movie5->text().toInt();
    int movie6=ui->movie6->text().toInt();
    QDate date1=ui->dateEdit->date();

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QString insertQuery = "INSERT INTO assign (date, am9, pm1, pm3, pm5, pm7, pm9) VALUES (:date1, :movie1, :movie2, :movie3, :movie4, :movie5, :movie6)";
        QSqlQuery insertSqlQuery;
        insertSqlQuery.prepare(insertQuery);
        insertSqlQuery.bindValue(":date1", QVariant(date1));
        insertSqlQuery.bindValue(":movie1", movie1);
        insertSqlQuery.bindValue(":movie2", movie2);
        insertSqlQuery.bindValue(":movie3", movie3);
        insertSqlQuery.bindValue(":movie4", movie4);
        insertSqlQuery.bindValue(":movie5", movie5);
        insertSqlQuery.bindValue(":movie6", movie6);
        if (insertSqlQuery.exec()) {
            QMessageBox::information(this, "排片成功", "该日期已完成排片！");
        } else {
            QMessageBox::critical(this, "错误", "assign表插入错误：" + insertSqlQuery.lastError().text());
            qDebug()<<insertSqlQuery.lastError().text();
        }
        Database::close();
    }

    ui->movie1->clear();
    ui->movie2->clear();
    ui->movie3->clear();
    ui->movie4->clear();
    ui->movie5->clear();
    ui->movie6->clear();
    ui->dateEdit->setReadOnly(false);

}

void assign::on_assign_check_clicked()
{
    ui->stack->setCurrentWidget(ui->assign_result);

}

void assign::on_assign_search_clicked()
{
    QDate date=ui->dateEdit_2->date();
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QString query="select date,am9,pm1,pm3,pm5,pm7,pm9 from assign where date= :date";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.bindValue(":date", QVariant(date));

        if(sqlQuery.exec())
        {
            if(sqlQuery.next()){
                ui->tableWidget_2->clearContents();
                ui->tableWidget_2->setRowCount(7);
                ui->tableWidget_2->setColumnCount(2);

                QString name;

                QString query2="select m_id,m_name from movie where m_id= :m_id";
                QSqlQuery sqlQuery2;
                sqlQuery2.prepare(query2);
                sqlQuery2.bindValue(":m_id", sqlQuery.value(1));


                QString query3="select m_id,m_name from movie where m_id= :m_id";
                QSqlQuery sqlQuery3;
                sqlQuery3.prepare(query3);
                sqlQuery3.bindValue(":m_id", sqlQuery.value(2));
                sqlQuery3.exec();

                QString query4="select m_id,m_name from movie where m_id= :m_id";
                QSqlQuery sqlQuery4;
                sqlQuery4.prepare(query4);
                sqlQuery4.bindValue(":m_id", sqlQuery.value(3));
                sqlQuery4.exec();

                QString query5="select m_id,m_name from movie where m_id= :m_id";
                QSqlQuery sqlQuery5;
                sqlQuery5.prepare(query5);
                sqlQuery5.bindValue(":m_id", sqlQuery.value(4));
                sqlQuery5.exec();

                QString query6="select m_id,m_name from movie where m_id= :m_id";
                QSqlQuery sqlQuery6;
                sqlQuery6.prepare(query6);
                sqlQuery6.bindValue(":m_id", sqlQuery.value(5));
                sqlQuery6.exec();

                QString query7="select m_id,m_name from movie where m_id= :m_id";
                QSqlQuery sqlQuery7;
                sqlQuery7.prepare(query7);
                sqlQuery7.bindValue(":m_id", sqlQuery.value(6));
                sqlQuery7.exec();

                QTableWidgetItem *columnItem0 = new QTableWidgetItem("日期：");
                ui->tableWidget_2->setItem(0,0, columnItem0);

                QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                            sqlQuery.value(0).toString());
                ui->tableWidget_2->setItem(0,1, columnItem1);

                QTableWidgetItem *columnItem2 = new QTableWidgetItem("9:00-11:00");
                ui->tableWidget_2->setItem(1,0, columnItem2);

                sqlQuery2.exec();
                if(sqlQuery2.next()){name=sqlQuery2.value(1).toString();}
                QTableWidgetItem *columnItem3 = new QTableWidgetItem(name);
                ui->tableWidget_2->setItem(1,1, columnItem3);

                QTableWidgetItem *columnItem4 = new QTableWidgetItem("13:00-15:00");
                ui->tableWidget_2->setItem(2,0, columnItem4);

                sqlQuery3.exec();
                if(sqlQuery3.next()){name=sqlQuery3.value(1).toString();}
                QTableWidgetItem *columnItem5 = new QTableWidgetItem(name);
                ui->tableWidget_2->setItem(2,1, columnItem5);

                QTableWidgetItem *columnItem6 = new QTableWidgetItem("15:00-17:00");
                ui->tableWidget_2->setItem(3,0, columnItem6);

                sqlQuery4.exec();
                if(sqlQuery4.next()){name=sqlQuery4.value(1).toString();}
                QTableWidgetItem *columnItem7 = new QTableWidgetItem(name);
                ui->tableWidget_2->setItem(3,1, columnItem7);

                QTableWidgetItem *columnItem8 = new QTableWidgetItem("17:00-19:00");
                ui->tableWidget_2->setItem(4,0, columnItem8);

                sqlQuery5.exec();
                if(sqlQuery5.next()){name=sqlQuery5.value(1).toString();}
                QTableWidgetItem *columnItem9 = new QTableWidgetItem(name);
                ui->tableWidget_2->setItem(4,1, columnItem9);

                QTableWidgetItem *columnItem10 = new QTableWidgetItem("19:00-21:00");
                ui->tableWidget_2->setItem(5,0, columnItem10);

                sqlQuery6.exec();
                if(sqlQuery6.next()){name=sqlQuery6.value(1).toString();}
                QTableWidgetItem *columnItem11 = new QTableWidgetItem(name);
                ui->tableWidget_2->setItem(5,1, columnItem11);

                QTableWidgetItem *columnItem12 = new QTableWidgetItem("21:00-23:00");
                ui->tableWidget_2->setItem(6,0, columnItem12);

                sqlQuery7.exec();
                if(sqlQuery7.next()){name=sqlQuery7.value(1).toString();}
                QTableWidgetItem *columnItem13 = new QTableWidgetItem(name);
                ui->tableWidget_2->setItem(6,1, columnItem13);

                ui->tableWidget_2->horizontalHeader()->setVisible(false); //隐藏水平表头
                ui->tableWidget_2->verticalHeader()->setVisible(false); //隐藏垂直表头
                ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            }
        } else {
            QMessageBox::critical(this, "错误", "该日期暂未进行排片,请联系管理员：" + sqlQuery.lastError().text());
        }
        Database::close();
    }
}

void assign::on_back_clicked()
{
    ui->stack->setCurrentWidget(ui->assign_page);

}
