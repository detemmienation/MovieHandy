#include "user.h"
#include "ui_user.h"
#include "userinfo.h"
#include "buy.h"
#include "vote.h"
#include <string>
#include <QMessageBox>

using namespace std;

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    A = new userinfo(this);
    A->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(A);
    ui->stackedWidget->setCurrentWidget(A);
    ui->info_button->setDown(true);
    B=NULL;
    C=NULL;
}

user::~user()
{
    delete ui;
}

void user::init(QString i,QString t,QString p)
{
    user_id=i;
    user_password=p;
    user_type=t;
}

void user::on_info_button_clicked()
{
    if(A)
    {
        ui->stackedWidget->removeWidget(A);
        delete A;
    }
    A= new userinfo(this);
    A->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(A);
    ui->stackedWidget->setCurrentWidget(A);
    ui->info_button->setDown(true);
    ui->buy_button->setDown(false);
    ui->vote_button->setDown(false);
}

void user::on_buy_button_clicked()
{
    if(B)
    {
        ui->stackedWidget->removeWidget(B);
        delete B;
    }
    B= new buy(this);
    B->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(B);
    ui->stackedWidget->setCurrentWidget(B);
    ui->info_button->setDown(false);
    ui->buy_button->setDown(true);
    ui->vote_button->setDown(false);
}

void user::on_vote_button_clicked()
{
    if(C)
    {
        ui->stackedWidget->removeWidget(C);
        delete C;
    }
    C= new vote(this);
    C->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(C);
    ui->stackedWidget->setCurrentWidget(C);
    ui->info_button->setDown(false);
    ui->buy_button->setDown(false);
    ui->vote_button->setDown(true);
}

void user::on_exit_button_clicked()
{
    QMessageBox::about(this,"提示","已退出");
        this->parentWidget()->show();
        delete this;
}
