//登陆及注册界面，要存储用户输入的账号、密码等数据在后续操作中使用
#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "user.h"
#include "admin.h"
namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_do_login_clicked();//登录按钮
    void on_do_register_clicked();//注册按钮
    void on_finish_register_clicked();//注册完成按钮


private:
    user *A;
    admin *B;
    Ui::login *ui;
};

#endif // LOGIN_H
