//管理员电影上下架页
#ifndef RENEW_H
#define RENEW_H

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QTableWidgetItem>
using namespace std;

namespace Ui {
class renew;
}

class renew : public QWidget
{
    Q_OBJECT

public:
    explicit renew(QWidget *parent = nullptr);
    ~renew();
    void init(QString i,QString t,QString p);

private slots:

    void on_gotoin_clicked();

    void on_gotode_clicked();

    void on_increase_clicked();//电影上架功能

    void on_decrease_clicked();//电影下架功能

    void on_refresh_clicked();

private:
    Ui::renew *ui;
    QString user_password,user_id,user_type;
};

#endif // SEARCH_H
