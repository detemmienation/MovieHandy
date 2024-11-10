//管理员类型左侧菜单界面
#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "admininfo.h"
#include "renew.h"
#include "assign.h"

using namespace std;

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    void init(QString i,QString t,QString p);

private slots:
    void on_info_button_clicked();//进入管理员信息页

    void on_renew_button_clicked();//进入电影上下架页

    void on_assign_button_clicked();//进入排片页

    void on_exit_button_clicked();//退出

private:
    Ui::admin *ui;
    admininfo *A;
    renew *B;
    assign *C;
    QString user_id,user_password,user_type;
};

#endif // ADMIN_H
