#include "vote.h"
#include "ui_vote.h"
#include <QSqlQuery>
#include "database.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QSqlError>
#include <QDebug>
#include<QDate>

vote::vote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vote)
{
    ui->setupUi(this);
}

vote::~vote()
{
    delete ui;
}

void vote::init(QString i, QString t, QString p)
{
    user_id = i;
    user_type = t;
    user_password = p;

    populateMovieComboBox();  // 填入电影选项
    populateTimeComboBox();  //填入时段选项
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
}

void vote::populateMovieComboBox()
{
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QSqlQuery query;
        // 执行查询语句，获取当前电影列表
        if (query.exec("SELECT m_name FROM movie WHERE flag=1"))
        {
            while (query.next())
            {
                QString movieName = query.value(0).toString();
                ui->comboBox_movie->addItem(movieName);
            }
        }
        else
        {
            qDebug() << "数据库查询错误：" << query.lastError().text();
        }
        Database::close();
    }
}

void vote::populateTimeComboBox()
{
    QString option1 = "am9";  // 填入时段选项
    QString option2 = "pm1";
    QString option3 = "pm3";
    QString option4 = "pm5";
    QString option5 = "pm7";
    QString option6 = "pm9";

    ui->comboBox_time->addItem(option1);
    ui->comboBox_time->addItem(option2);
    ui->comboBox_time->addItem(option3);
    ui->comboBox_time->addItem(option4);
    ui->comboBox_time->addItem(option5);
    ui->comboBox_time->addItem(option6);
}

void vote::on_assign_search_clicked()
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
                ui->tableWidget->clearContents();
                ui->tableWidget->setRowCount(7);
                ui->tableWidget->setColumnCount(2);

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
                ui->tableWidget->setItem(0,0, columnItem0);

                QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                            sqlQuery.value(0).toString());
                ui->tableWidget->setItem(0,1, columnItem1);

                QTableWidgetItem *columnItem2 = new QTableWidgetItem("9:00-11:00");
                ui->tableWidget->setItem(1,0, columnItem2);

                sqlQuery2.exec();
                if(sqlQuery2.next()){name=sqlQuery2.value(1).toString();}
                QTableWidgetItem *columnItem3 = new QTableWidgetItem(name);
                ui->tableWidget->setItem(1,1, columnItem3);

                QTableWidgetItem *columnItem4 = new QTableWidgetItem("13:00-15:00");
                ui->tableWidget->setItem(2,0, columnItem4);

                sqlQuery3.exec();
                if(sqlQuery3.next()){name=sqlQuery3.value(1).toString();}
                QTableWidgetItem *columnItem5 = new QTableWidgetItem(name);
                ui->tableWidget->setItem(2,1, columnItem5);

                QTableWidgetItem *columnItem6 = new QTableWidgetItem("15:00-17:00");
                ui->tableWidget->setItem(3,0, columnItem6);

                sqlQuery4.exec();
                if(sqlQuery4.next()){name=sqlQuery4.value(1).toString();}
                QTableWidgetItem *columnItem7 = new QTableWidgetItem(name);
                ui->tableWidget->setItem(3,1, columnItem7);

                QTableWidgetItem *columnItem8 = new QTableWidgetItem("17:00-19:00");
                ui->tableWidget->setItem(4,0, columnItem8);

                sqlQuery5.exec();
                if(sqlQuery5.next()){name=sqlQuery5.value(1).toString();}
                QTableWidgetItem *columnItem9 = new QTableWidgetItem(name);
                ui->tableWidget->setItem(4,1, columnItem9);

                QTableWidgetItem *columnItem10 = new QTableWidgetItem("19:00-21:00");
                ui->tableWidget->setItem(5,0, columnItem10);

                sqlQuery6.exec();
                if(sqlQuery6.next()){name=sqlQuery6.value(1).toString();}
                QTableWidgetItem *columnItem11 = new QTableWidgetItem(name);
                ui->tableWidget->setItem(5,1, columnItem11);

                QTableWidgetItem *columnItem12 = new QTableWidgetItem("21:00-23:00");
                ui->tableWidget->setItem(6,0, columnItem12);

                sqlQuery7.exec();
                if(sqlQuery7.next()){name=sqlQuery7.value(1).toString();}
                QTableWidgetItem *columnItem13 = new QTableWidgetItem(name);
                ui->tableWidget->setItem(6,1, columnItem13);

                ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏水平表头
                ui->tableWidget->verticalHeader()->setVisible(false); //隐藏垂直表头
                ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            }
        } else {
            QMessageBox::critical(this, "错误", "该日期暂未进行排片，请联系管理员：" + sqlQuery.lastError().text());
        }
        Database::close();
    }
}

void vote::on_Vote_clicked()
{
    QString preferredMovie = ui->comboBox_movie->currentText();  // 获取偏好电影
    QDate preferredDate = ui->dateEdit->date();  // 获取偏好观影日期
    QString preferredTime = ui->comboBox_time->currentText();  //获取偏好时间

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QString getmid = "SELECT m_id FROM movie WHERE m_name =:name";
        QSqlQuery query;
        query.prepare(getmid);
        query.bindValue(":name", preferredMovie);
        query.exec();
        if (query.exec()) {
            if (query.next()) {
                int m_id = query.value(0).toInt();
                QString insertQuery = "INSERT INTO vote (u_id, date, time, m_id) VALUES (:u_id, :date, :time, :m_id)";
                QSqlQuery insertSqlQuery;
                insertSqlQuery.prepare(insertQuery);
                insertSqlQuery.bindValue(":u_id", user_id);
                insertSqlQuery.bindValue(":date", QVariant(preferredDate));
                insertSqlQuery.bindValue(":time", preferredTime);
                insertSqlQuery.bindValue(":m_id", m_id);
                if (insertSqlQuery.exec()) {
                    QMessageBox::information(this, "投票成功", "已根据用户活跃度完成投票！");
                    QSqlQuery query;
                    query.exec("UPDATE user SET u_act=u_act+0.1 WHERE u_id="+user_id+"");
                } else {
                    QMessageBox::critical(this, "错误", "请勿重复投票：" + insertSqlQuery.lastError().text());
                }
            }
        } else {
            // 查询执行失败
            QMessageBox::critical(this, "错误", "movie表查询错误" + query.lastError().text());
            // 处理查询失败的情况
        }


        update_vote_result();
        Database::close();
    }
}

void vote::update_vote_result()
{
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        // 遍历vote表中的每个元组
        QSqlQuery query("SELECT u_id, date, time, m_id FROM vote");
        while (query.next()) {
            int u_id = query.value(0).toInt();
            QDate date = query.value(1).toDate();
            QString time = query.value(2).toString();
            int m_id = query.value(3).toInt();

            // 根据u_id查询user表获取u_act值
            QSqlQuery userQuery;
            userQuery.prepare("SELECT u_act FROM user WHERE u_id = :u_id");
            userQuery.bindValue(":u_id", u_id);
            if (userQuery.exec() && userQuery.next()) {
                int u_act = userQuery.value(0).toInt();
                int vote_num;
                if(u_act<10){
                    vote_num=1;
                }else{
                    if(u_act<20){
                        vote_num=2;
                    }else{
                        vote_num=3;
                    }
                }

                // 更新vote_result表中对应的属性
                QSqlQuery updateQuery;
                updateQuery.prepare("INSERT INTO vote_result (m_id, date, am9, pm1, pm3, pm5, pm7, pm9) "
                                    "VALUES (:m_id, :date, :am9, :pm1, :pm3, :pm5, :pm7, :pm9) "
                                    "ON DUPLICATE KEY UPDATE "
                                    "am9 = am9 + :am9, pm1 = pm1 + :pm1, pm3 = pm3 + :pm3, "
                                    "pm5 = pm5 + :pm5, pm7 = pm7 + :pm7, pm9 = pm9 + :pm9");
                updateQuery.bindValue(":m_id", m_id);
                updateQuery.bindValue(":date", date);
                updateQuery.bindValue(":am9", (time == "am9") ? vote_num : 0);
                updateQuery.bindValue(":pm1", (time == "pm1") ? vote_num : 0);
                updateQuery.bindValue(":pm3", (time == "pm3") ? vote_num : 0);
                updateQuery.bindValue(":pm5", (time == "pm5") ? vote_num : 0);
                updateQuery.bindValue(":pm7", (time == "pm7") ? vote_num : 0);
                updateQuery.bindValue(":pm9", (time == "pm9") ? vote_num : 0);

                if (!updateQuery.exec()) {
                    // 处理插入/更新失败的情况
                    QMessageBox::critical(this, "错误", "vote_result插入或更新错误：" + updateQuery.lastError().text());
                }
            }
            else {
                // 处理查询u_act失败的情况
                QMessageBox::critical(this, "错误", "u_act查询错误：" + userQuery.lastError().text());
            }
        }
        Database::close();
    }
}
