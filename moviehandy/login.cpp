#include "login.h"
#include "user.h"
#include "admin.h"
#include "ui_login.h"
#include "database.h"
#include<QApplication>
#include<QDebug>
#include<QSqlDatabase>

#include<QSqlQuery>
#include<QSqlError>
#include <QMessageBox>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

//补全登录功能
void login::on_do_login_clicked()
{
    QString user_password = ui->login_password->text();
    QString user_id = ui->login_id->text();
    QString user_type;

    // 查询数据库表user，根据u_id匹配账号是否存在
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QString query = "SELECT* FROM user WHERE u_id =:id AND u_pass =:pass";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.bindValue(":id", user_id);
        sqlQuery.bindValue(":pass", user_password);
        if (sqlQuery.exec()) {
            // 如果查询结果非空，表示密码匹配成功
            if (sqlQuery.next()) {
                int userType = sqlQuery.value("u_type").toInt();
                if (userType == 0) {
                    // 进入管理员界面admin
                    B = new admin();
                    B->init(user_id,user_type,user_password);
                    B->show();
                    this->hide();
                    ui->login_id->clear();
                    ui->login_password->clear();
                } else {
                    // 进入用户界面user
                    A = new user();
                    A->init(user_id,user_type,user_password);
                    A->show();
                    this->hide();
                    ui->login_id->clear();
                    ui->login_password->clear();
                }
            } else {
                QMessageBox::warning(this, "登录失败", "账号或密码输入有误！");
                ui->login_id->clear();
                ui->login_password->clear();
            }
        } else {
        // 查询出错的处理逻辑
        QMessageBox::critical(this, "错误", "数据库查询错误：" + sqlQuery.lastError().text());
        }
        Database::close();
    }
}

void login::on_do_register_clicked()
{
    ui->register_id->clear();
    ui->register_password->clear();
    ui->register_password_2->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void login::on_finish_register_clicked()
{
    QString u_id = ui->register_id->text();
    QString u_pass = ui->register_password->text();
    QString u_pass2 = ui->register_password_2->text();

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();

        QString query = "SELECT u_id FROM user WHERE u_id = :id";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        // 绑定参数
        sqlQuery.bindValue(":id", u_id);
        // 执行查询
        if (sqlQuery.exec()) {
            if (sqlQuery.next()) {
                QMessageBox::warning(this, "注册失败", "该账号id已存在，请重新输入！");
                ui->register_id->clear();
                ui->register_password->clear();
                ui->register_password_2->clear();
            } else {
                if (u_pass != u_pass2) {
                    QMessageBox::warning(this, "注册失败", "两次密码输入不一致！");
                    ui->register_password->clear();
                    ui->register_password_2->clear();
                } else {
                    // 向数据库user表插入新用户信息，u_type默认为1
                    QString insertQuery = "INSERT INTO user (u_id, u_pass, u_type, u_act) VALUES (:id, :pass, 1, 0)";
                    QSqlQuery insertSqlQuery;
                    insertSqlQuery.prepare(insertQuery);
                    // 绑定参数
                    insertSqlQuery.bindValue(":id", u_id);
                    insertSqlQuery.bindValue(":pass", u_pass);
                    // 执行插入
                    if (insertSqlQuery.exec()) {
                        QMessageBox::information(this, "注册成功", "注册成功，请登录！");
                        ui->stackedWidget->setCurrentIndex(0);
                    } else {
                        QMessageBox::critical(this, "错误", "数据库插入错误：" + insertSqlQuery.lastError().text());
                    }
                }
            }
        } else {
            QMessageBox::critical(this, "错误", "数据库查询错误：" + sqlQuery.lastError().text());
        }
    Database::close();
    }
}
