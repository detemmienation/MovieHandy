//用户中心内容页
#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QTableWidgetItem>
using namespace std;

namespace Ui {
class userinfo;
}

class userinfo : public QWidget
{
    Q_OBJECT

public:
    explicit userinfo(QWidget *parent = nullptr);
    ~userinfo();
    void init(QString i,QString t,QString p);

private slots:

    void on_buy_search_clicked();//订单查询操作，将该用户所有订单显示在表格中

    void on_vote_search_clicked();//投票查询操作，将该用户所有投票显示在表格中

    void on_back_toinfo1_clicked();

    void on_back_toinfo2_clicked();


private:
    Ui::userinfo *ui;
    QString user_password,user_id,user_type;
    QString b_id;
    QString d_id;
};

#endif // SEARCH_H
