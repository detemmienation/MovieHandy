//用户类型左侧菜单界面
#ifndef USER_H
#define USER_H

#include <QWidget>
#include "userinfo.h"
#include "buy.h"
#include "vote.h"

using namespace std;

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();
    void init(QString i,QString t,QString p);

private slots:
    void on_info_button_clicked();//进入用戶信息页

    void on_vote_button_clicked();//进入投票页

    void on_buy_button_clicked();//进入购票页

    void on_exit_button_clicked();//退出

private:
    Ui::user *ui;
    userinfo *A;
    buy *B;
    vote *C;
    QString user_id,user_password,user_type;
};

#endif // USER_H
