//管理员中心页
#ifndef ADMININFO_H
#define ADMININFO_H

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QTableWidgetItem>
using namespace std;

namespace Ui {
class admininfo;
}

class admininfo : public QWidget
{
    Q_OBJECT

public:
    explicit admininfo(QWidget *parent = nullptr);
    ~admininfo();
    void init(QString i,QString t,QString p);

private slots:

    void on_do_manage_clicked();//进入管理用户页面

    void on_do_update_clicked();//更新用户信息

    void on_do_delete_clicked();//删除用户信息

    void on_back_clicked();


    void on_refresh_clicked();

private:
    Ui::admininfo *ui;
    QString user_password,user_id,user_type;
    QString b_id;
    QString d_id;
};

#endif // ADMININFO_H
