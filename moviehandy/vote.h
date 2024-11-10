//用户投票页
#ifndef VOTE_H
#define VOTE_H

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QTableWidgetItem>
#include<QDate>
using namespace std;

namespace Ui {
class vote;
}

class vote : public QWidget
{
    Q_OBJECT

public:
    explicit vote(QWidget *parent = nullptr);
    ~vote();
    void init(QString i,QString t,QString p);

private slots:

    void on_Vote_clicked();

    void populateMovieComboBox();

    void populateTimeComboBox();

    void update_vote_result();

    void on_assign_search_clicked();

private:
    Ui::vote *ui;
    QString user_password,user_id,user_type;
};

#endif // VOTE_H
