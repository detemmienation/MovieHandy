//管理员排片页
#ifndef ASSIGN_H
#define ASSIGN_H

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QTableWidgetItem>
using namespace std;

namespace Ui {
class assign;
}

class assign : public QWidget
{
    Q_OBJECT

public:
    explicit assign(QWidget *parent = nullptr);
    ~assign();
    void init(QString i,QString t,QString p);

private slots:

    void on_do_assign_clicked();//进行排片

    void on_date_select_clicked();//进行排片日期选择

    void on_back_clicked();

    void on_assign_check_clicked();//查看排片表

    void on_assign_search_clicked();

private:
    Ui::assign *ui;
    QString user_password,user_id,user_type;

};

#endif // ASSIGN_H
