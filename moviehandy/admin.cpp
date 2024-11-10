#include "admin.h"
#include "ui_admin.h"
#include "admininfo.h"
#include "renew.h"
#include "assign.h"
#include <string>
#include <QMessageBox>

using namespace std;

admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    A = new admininfo(this);
    A->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(A);
    ui->stackedWidget->setCurrentWidget(A);
    ui->info_button->setDown(true);
    B=NULL;
    C=NULL;
}

admin::~admin()
{
    delete ui;
}

void admin::init(QString i,QString t,QString p)
{
    user_id=i;
    user_password=p;
    user_type=t;
}

void admin::on_renew_button_clicked()
{
    if(B)
    {
        ui->stackedWidget->removeWidget(B);
        delete B;
    }
    B= new renew(this);
    B->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(B);
    ui->stackedWidget->setCurrentWidget(B);
    ui->info_button->setDown(false);
    ui->renew_button->setDown(true);
    ui->assign_button->setDown(false);
}

void admin::on_assign_button_clicked()
{
    if(C)
    {
        ui->stackedWidget->removeWidget(C);
        delete C;
    }
    C= new assign(this);
    C->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(C);
    ui->stackedWidget->setCurrentWidget(C);
    ui->info_button->setDown(false);
    ui->renew_button->setDown(false);
    ui->assign_button->setDown(true);
}

void admin::on_exit_button_clicked()
{
    QMessageBox::about(this,"提示","已退出");
        this->parentWidget()->show();
        delete this;
}

void admin::on_info_button_clicked()
{
    if(A)
    {
        ui->stackedWidget->removeWidget(A);
        delete A;
    }
    A= new admininfo(this);
    A->init(user_id,user_type,user_password);
    ui->stackedWidget->addWidget(A);
    ui->stackedWidget->setCurrentWidget(A);
    ui->info_button->setDown(true);
    ui->renew_button->setDown(false);
    ui->assign_button->setDown(false);
}
