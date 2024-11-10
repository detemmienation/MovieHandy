//用户购票页
#ifndef BUY_H
#define BUY_H

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QTableWidgetItem>
using namespace std;

namespace Ui {
class buy;
}

class buy : public QWidget
{
    Q_OBJECT

public:
    explicit buy(QWidget *parent = nullptr);
    ~buy();
    void init(QString i,QString t,QString p);

private slots:

    void on_query_clicked();//筛选符合用户设置的条件的电影

    void on_select_clicked();//选择指定场次的电影后前往选座页面

    void on_lock_clicked();//锁座，转向支付页面

    void on_back_clicked();//返回查询页面

    void on_select_3_clicked();

    void on_select_4_clicked();

    void on_select_5_clicked();

    void on_select_6_clicked();

    void on_select_7_clicked();

    void on_s11_stateChanged(int arg1);

    void on_s12_stateChanged(int arg1);

    void on_s13_stateChanged(int arg1);

    void on_s14_stateChanged(int arg1);

    void on_s15_stateChanged(int arg1);

    void on_s16_stateChanged(int arg1);

    void on_s21_stateChanged(int arg1);

    void on_s22_stateChanged(int arg1);

    void on_s23_stateChanged(int arg1);

    void on_s24_stateChanged(int arg1);

    void on_s25_stateChanged(int arg1);

    void on_s26_stateChanged(int arg1);

    void on_s31_stateChanged(int arg1);

    void on_s32_stateChanged(int arg1);

    void on_s33_stateChanged(int arg1);

    void on_s34_stateChanged(int arg1);

    void on_s35_stateChanged(int arg1);

    void on_s36_stateChanged(int arg1);

    void on_s41_stateChanged(int arg1);

    void on_s42_stateChanged(int arg1);

    void on_s43_stateChanged(int arg1);

    void on_s44_stateChanged(int arg1);

    void on_s45_stateChanged(int arg1);

    void on_s46_stateChanged(int arg1);

    void on_s51_stateChanged(int arg1);

    void on_s52_stateChanged(int arg1);

    void on_s53_stateChanged(int arg1);

    void on_s54_stateChanged(int arg1);

    void on_s55_stateChanged(int arg1);

    void on_s56_stateChanged(int arg1);

    void on_pay_clicked();

private:
    Ui::buy *ui;
    QString user_password,user_id,user_type;
};

#endif // BUY_H
