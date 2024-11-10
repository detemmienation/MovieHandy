#include "buy.h"
#include "ui_buy.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QMessageBox>
#include "database.h"
#include <vector>
#include<QDebug>
#include <QSqlError>
#include<QDate>
using namespace std;

//string类型方便转化为命令
QString u_id;//用户名 int
QString m_id;//实际上对应查片表键值p_id int
vector<int>movie_select(6);
vector<QString>movie_name(6);//电影名
int sel;
vector<vector<int>>seat_init(5,vector<int>(6));//选座前的座位表,用于初始化座位状态
vector<vector<int>>seat_last(5,vector<int>(6));//选座的记录表

int num=0;//票数

buy::buy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buy)
{
    ui->setupUi(this);

}

buy::~buy()
{
    delete ui;
}

void buy::init(QString i,QString t,QString p)
{
    user_id=i;
    user_type=t;
    user_password=p;
    u_id=i;
    //初始化查片表
    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery sql_query(db);
        sql_query.exec("DROP TABLE query");//删除上一轮的查片表
        sql_query.exec("create table query (date date,m_id int,time varchar(255),m_type varchar(255),p_id int primary key)");//新的查片表

        sql_query.exec("SELECT * FROM assign");
        int id=0;//即将要填入的p_id
        while(sql_query.next()){
            QSqlQuery zanshi(db);

            QString sql="INSERT INTO query (date,m_id,time,m_type,p_id) VALUES ('"+sql_query.value("date").toString()+"',";//date
            sql+=sql_query.value("am9").toString()+",";//m_id
            sql+="'9:00-11:00',";
            sql+="'xxx',";
            QString s = QString::number(id);
            sql+=s+")";
            id++;
            zanshi.exec(sql);

            sql="INSERT INTO query (date,m_id,time,m_type,p_id) VALUES ('"+sql_query.value("date").toString()+"',";//date
            sql+=sql_query.value("pm1").toString()+",";//m_id
            sql+="'13:00-15:00',";
            sql+="'xxx',";
            s = QString::number(id);
            sql+=s+")";
            id++;
            zanshi.exec(sql);

            sql="INSERT INTO query (date,m_id,time,m_type,p_id) VALUES ('"+sql_query.value("date").toString()+"',";//date
            sql+=sql_query.value("pm3").toString()+",";//m_id
            sql+="'15:00-17:00',";
            sql+="'xxx',";
            s = QString::number(id);
            sql+=s+")";
            id++;
            zanshi.exec(sql);

            sql="INSERT INTO query (date,m_id,time,m_type,p_id) VALUES ('"+sql_query.value("date").toString()+"',";//date
            sql+=sql_query.value("pm5").toString()+",";//m_id
            sql+="'17:00-19:00',";
            sql+="'xxx',";
            s = QString::number(id);
            sql+=s+")";
            id++;
            zanshi.exec(sql);

            sql="INSERT INTO query (date,m_id,time,m_type,p_id) VALUES ('"+sql_query.value("date").toString()+"',";//date
            sql+=sql_query.value("pm7").toString()+",";//m_id
            sql+="'19:00-21:00',";
            sql+="'xxx',";
            s = QString::number(id);
            sql+=s+")";
            id++;
            zanshi.exec(sql);

            sql="INSERT INTO query (date,m_id,time,m_type,p_id) VALUES ('"+sql_query.value("date").toString()+"',";//date
            sql+=sql_query.value("pm9").toString()+",";//m_id
            sql+="'21:00-23:00',";
            sql+="'xxx',";
            s = QString::number(id);
            sql+=s+")";
            id++;
            zanshi.exec(sql);

        }
        Database::close();//查片表插入完成
    }

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery name = db.exec("select m_name from movie where flag=1 group by m_name");
        QSqlQuery time= db.exec("select time from query group by time");
        QSqlQuery date= db.exec("select date from query group by date");
    while(name.next()){//为combobox填入选项
            ui->comboBox_1->addItem(name.value("m_name").toString());
    }
    while(time.next()){//为combobox填入选项
            ui->comboBox_3->addItem(time.value("time").toString());
    }
    while(date.next()){//为combobox填入选项
            ui->comboBox_2->addItem(date.value("date").toString());
    }
        Database::close();
    }

}

void buy::on_query_clicked()
{
    ui->select->setText("###");
    ui->select_3->setText("###");
    ui->select_4->setText("###");
    ui->select_5->setText("###");
    ui->select_6->setText("###");
    ui->select_7->setText("###");

    QString command;
    command="select * from query where";
    if(ui->checkBox_1->isChecked()){
    //要确保日期的格式是DATE
        command.append(" date='"+ui->comboBox_2->currentText()+"'");
    }

    if(ui->checkBox_2->isChecked()){
        if(!ui->checkBox_1->isChecked())//只查询时间
        command.append(" time='"+ui->comboBox_3->currentText()+"'");
        else
        command.append(" and time='"+ui->comboBox_3->currentText()+"'");
    }
    QSqlQuery result;

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        result = db.exec(command);

        QSqlQuery movie;//电影数据
        if(result.next()){//设置选项表
            movie.exec("select m_name from movie where m_id="+result.value("m_id").toString());
            movie.next();//获取数据
            QString info=result.value("date").toString()+movie.value("m_name").toString()+result.value("time").toString();
            ui->select->setText(info);
            movie_select[0]=result.value("p_id").toInt();
            movie_name[0]=movie.value("m_name").toString();
        if(result.next()){
                movie.exec("select m_name from movie where m_id="+result.value("m_id").toString());
                movie.next();//获取数据
                QString info=result.value("date").toString()+" "+movie.value("m_name").toString()+" "+result.value("time").toString();
                ui->select_3->setText(info);
                movie_select[1]=result.value("p_id").toInt();
                movie_name[1]=movie.value("m_name").toString();
                if(result.next()){
                    movie.exec("select m_name from movie where m_id="+result.value("m_id").toString());
                    movie.next();//获取数据
                    QString info=result.value("date").toString()+" "+movie.value("m_name").toString()+" "+result.value("time").toString();
                    ui->select_4->setText(info);
                    movie_select[2]=result.value("p_id").toInt();
                    movie_name[2]=movie.value("m_name").toString();
                    if(result.next()){
                        movie.exec("select m_name from movie where m_id="+result.value("m_id").toString());
                        movie.next();//获取数据
                        QString info=result.value("date").toString()+" "+movie.value("m_name").toString()+" "+result.value("time").toString();
                        ui->select_5->setText(info);
                        movie_select[3]=result.value("p_id").toInt();
                        movie_name[3]=movie.value("m_name").toString();
                        if(result.next()){
                            movie.exec("select m_name from movie where m_id="+result.value("m_id").toString());
                            movie.next();//获取数据
                            QString info=result.value("date").toString()+" "+movie.value("m_name").toString()+" "+result.value("time").toString();
                            ui->select_6->setText(info);
                            movie_select[4]=result.value("p_id").toInt();
                            movie_name[4]=movie.value("m_name").toString();
                            if(result.next()){
                                movie.exec("select m_name from movie where m_id="+result.value("m_id").toString());
                                movie.next();//获取数据
                                QString info=result.value("date").toString()+" "+movie.value("m_name").toString()+" "+result.value("time").toString();
                                ui->select_7->setText(info);
                                movie_select[5]=result.value("p_id").toInt();
                                movie_name[5]=movie.value("m_name").toString();
                            }
                        }
                    }
                }
        }
        }

        Database::close();
    }

}

void buy::on_select_clicked()
{
    QString info=ui->select->text()[0];
    if(info!="#"){
    sel=0;
    //初始化座位
    if (Database::connect()) {
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                QString sql="SELECT * FROM buy WHERE seat='"+QString::number(i)+"";
                sql+=",";
                sql+=""+QString::number(j)+"'";//访问buy表
                sql+=" and m_id="+QString::number(movie_select[sel]);
                sql_query.exec(sql);
                if(sql_query.first()){
                    seat_init[i][j]=1;
                }
                else{
                    seat_init[i][j]=0;
                }
            }

    }

    Database::close();
    }

    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
            QString name="s"+QString::number(i+1)+QString::number(j+1);
            if(seat_init[i][j]==1){
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setChecked(true);
                now->setEnabled(false);
            }
    }
    }
    for(int i=0;i<5;i++){//选坐表置为空
            for (int j = 0; j < 6; j++) {
                seat_last[i][j]=0;
            }
    }
    num=0;
    ui->number->setText(QString::number(num));
    ui->stack->setCurrentWidget(ui->select_page);
    }
}

void buy::on_lock_clicked()//输出发票
{
    if(num==0){
    QMessageBox::about(this, tr("提示"), tr("请选择至少一个座位"));
    }
    else{
    QString result;
    result="共购买"+QString::number(num)+"张票\n";
    result+="电影名："+movie_name[sel]+"\n";
    if (Database::connect()) {//查表获取时间
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    sql_query.exec("SELECT * FROM query WHERE p_id="+QString::number(movie_select[sel]));
    sql_query.next();
    result+="播放时间："+sql_query.value("date").toString()+" "+sql_query.value("time").toString()+"\n";
    Database::close();
    }
    result+="座位号:\n";
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
                if(seat_last[i][j]==1){
                result+=QString::number(i+1)+"排"+QString::number(j+1)+"列\n";
                }
        }
    }
    ui->textBrowser_4->insertPlainText(result);//输出到textbrowser
    ui->textBrowser_4->moveCursor(QTextCursor::End);//将光标移动到当前文字最后
    ui->stack->setCurrentWidget(ui->pay_page);
    }
}

void buy::on_back_clicked()
{
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
        if(seat_last[i][j]==1||seat_init[i][j]==1){
                QString name="s"+QString::number(i+1)+QString::number(j+1);
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setEnabled(true);
                now->setChecked(false);
        }
    }
    }
    num=0;
    ui->textBrowser_4->clear();
    ui->stack->setCurrentWidget(ui->query_page);
}

void buy::on_select_3_clicked()
{
    QString info=ui->select->text()[0];
    if(info!="#"){
    sel=1;
    //初始化座位
    if (Database::connect()) {
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                QString sql="SELECT * FROM buy WHERE seat='"+QString::number(i)+"";
                sql+=",";
                sql+=""+QString::number(j)+"'";//访问buy表
                sql+=" and m_id="+QString::number(movie_select[sel]);
                sql_query.exec(sql);
                if(sql_query.first()){
                    seat_init[i][j]=1;
                }
                else{
                    seat_init[i][j]=0;
                }
            }

    }
    Database::close();
    }
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
            QString name="s"+QString::number(i+1)+QString::number(j+1);
            if(seat_init[i][j]==1){
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setChecked(true);
                now->setEnabled(false);
            }
    }
    }
    for(int i=0;i<5;i++){//选坐表置为空
    for (int j = 0; j < 6; j++) {
            seat_last[i][j]=0;
    }
    }
    num=0;
    ui->number->setText(QString::number(num));
    ui->stack->setCurrentWidget(ui->select_page);
    }
}

void buy::on_select_4_clicked()
{
    QString info=ui->select->text()[0];
    if(info!="#"){
    sel=2;
    //初始化座位
    if (Database::connect()) {
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                QString sql="SELECT * FROM buy WHERE seat='"+QString::number(i)+"";
                sql+=",";
                sql+=""+QString::number(j)+"'";//访问buy表
                sql+=" and m_id="+QString::number(movie_select[sel]);
                sql_query.exec(sql);
                if(sql_query.first()){
                    seat_init[i][j]=1;
                }
                else{
                    seat_init[i][j]=0;
                }
            }

    }
    Database::close();
    }
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
            QString name="s"+QString::number(i+1)+QString::number(j+1);
            if(seat_init[i][j]==1){
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setChecked(true);
                now->setEnabled(false);
            }
    }
    }
    for(int i=0;i<5;i++){//选坐表置为空
    for (int j = 0; j < 6; j++) {
            seat_last[i][j]=0;
    }
    }
    num=0;
    ui->number->setText(QString::number(num));
    ui->stack->setCurrentWidget(ui->select_page);
    }
}

void buy::on_select_5_clicked()
{
    QString info=ui->select->text()[0];
    if(info!="#"){
    sel=3;
    //初始化座位
    if (Database::connect()) {
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                QString sql="SELECT * FROM buy WHERE seat='"+QString::number(i)+"";
                sql+=",";
                sql+=""+QString::number(j)+"'";//访问buy表
                sql+=" and m_id="+QString::number(movie_select[sel]);
                sql_query.exec(sql);
                if(sql_query.first()){
                    seat_init[i][j]=1;
                }
                else{
                    seat_init[i][j]=0;
                }
            }

    }
    Database::close();
    }
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
            QString name="s"+QString::number(i+1)+QString::number(j+1);
            if(seat_init[i][j]==1){
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setChecked(true);
                now->setEnabled(false);
            }
    }
    }
    for(int i=0;i<5;i++){//选坐表置为空
    for (int j = 0; j < 6; j++) {
            seat_last[i][j]=0;
    }
    }
    num=0;
    ui->number->setText(QString::number(num));
    ui->stack->setCurrentWidget(ui->select_page);
    }
}

void buy::on_select_6_clicked()
{
    QString info=ui->select->text()[0];
    if(info!="#"){
    sel=4;
    //初始化座位
    if (Database::connect()) {
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                QString sql="SELECT * FROM buy WHERE seat='"+QString::number(i)+"";
                sql+=",";
                sql+=""+QString::number(j)+"'";//访问buy表
                sql+=" and m_id="+QString::number(movie_select[sel]);
                sql_query.exec(sql);
                if(sql_query.first()){
                    seat_init[i][j]=1;
                }
                else{
                    seat_init[i][j]=0;
                }
            }

    }
    Database::close();
    }
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
            QString name="s"+QString::number(i+1)+QString::number(j+1);
            if(seat_init[i][j]==1){
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setChecked(true);
                now->setEnabled(false);
            }
    }
    }
    for(int i=0;i<5;i++){//选坐表置为空
    for (int j = 0; j < 6; j++) {
            seat_last[i][j]=0;
    }
    }
    num=0;
    ui->number->setText(QString::number(num));
    ui->stack->setCurrentWidget(ui->select_page);
    }
}


void buy::on_select_7_clicked()
{
    QString info=ui->select->text()[0];
    if(info!="#"){
    sel=5;
    //初始化座位
    if (Database::connect()) {
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery sql_query(db);
    for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                QString sql="SELECT * FROM buy WHERE seat='"+QString::number(i)+"";
                sql+=",";
                sql+=""+QString::number(j)+"'";//访问buy表
                sql+=" and m_id="+QString::number(movie_select[sel]);
                sql_query.exec(sql);
                if(sql_query.first()){
                    seat_init[i][j]=1;
                }
                else{
                    seat_init[i][j]=0;
                }
            }

    }
    Database::close();
    }
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
            QString name="s"+QString::number(i+1)+QString::number(j+1);
            if(seat_init[i][j]==1){
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setChecked(true);
                now->setEnabled(false);

            }
    }
    }
    for(int i=0;i<5;i++){//选坐表置为空
    for (int j = 0; j < 6; j++) {
            seat_last[i][j]=0;
    }
    }
    num=0;
    ui->number->setText(QString::number(num));
    ui->stack->setCurrentWidget(ui->select_page);
    }
}


void buy::on_s11_stateChanged(int arg1)
{

    if(ui->s11->isChecked()){
    num+=1;
    seat_last[0][0]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[0][0]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s12_stateChanged(int arg1)
{
    if(ui->s12->isChecked()){
    num+=1;
    seat_last[0][1]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[0][1]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s13_stateChanged(int arg1)
{
    if(ui->s13->isChecked()){
    num+=1;
    seat_last[0][2]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[0][2]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s14_stateChanged(int arg1)
{
    if(ui->s14->isChecked()){
    num+=1;
    seat_last[0][3]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[0][3]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s15_stateChanged(int arg1)
{
    if(ui->s15->isChecked()){
    num+=1;
    seat_last[0][4]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[0][4]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s16_stateChanged(int arg1)
{
    if(ui->s16->isChecked()){
    num+=1;
    seat_last[0][5]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[0][5]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s21_stateChanged(int arg1)
{
    if(ui->s21->isChecked()){
    num+=1;
    seat_last[1][0]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[1][0]=0;
    ui->number->setText(QString::number(num));
    }

}


void buy::on_s22_stateChanged(int arg1)
{
    if(ui->s22->isChecked()){
    num+=1;
    seat_last[1][1]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[1][1]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s23_stateChanged(int arg1)
{
    if(ui->s23->isChecked()){
    num+=1;
    seat_last[1][2]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[1][2]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s24_stateChanged(int arg1)
{
    if(ui->s24->isChecked()){
    num+=1;
    seat_last[1][3]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[1][3]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s25_stateChanged(int arg1)
{
    if(ui->s25->isChecked()){
    num+=1;
    seat_last[1][4]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[1][4]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s26_stateChanged(int arg1)
{
    if(ui->s26->isChecked()){
    num+=1;
    seat_last[1][5]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[1][5]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s31_stateChanged(int arg1)
{
    if(ui->s31->isChecked()){
    num+=1;
    seat_last[2][0]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[2][0]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s32_stateChanged(int arg1)
{
    if(ui->s32->isChecked()){
    num+=1;
    seat_last[2][1]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[2][1]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s33_stateChanged(int arg1)
{
    if(ui->s33->isChecked()){
    num+=1;
    seat_last[2][2]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[2][2]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s34_stateChanged(int arg1)
{
    if(ui->s34->isChecked()){
    num+=1;
    seat_last[2][3]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[2][3]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s35_stateChanged(int arg1)
{
    if(ui->s35->isChecked()){
    num+=1;
    seat_last[2][4]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[2][4]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s36_stateChanged(int arg1)
{
    if(ui->s36->isChecked()){
    num+=1;
    seat_last[2][5]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[2][5]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s41_stateChanged(int arg1)
{
    if(ui->s41->isChecked()){
    num+=1;
    seat_last[3][0]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[3][0]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s42_stateChanged(int arg1)
{
    if(ui->s42->isChecked()){
    num+=1;
    seat_last[3][1]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[3][1]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s43_stateChanged(int arg1)
{
    if(ui->s43->isChecked()){
    num+=1;
    seat_last[3][2]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[3][2]=0;
    ui->number->setText(QString::number(num));
    }
}



void buy::on_s44_stateChanged(int arg1)
{
    if(ui->s44->isChecked()){
    num+=1;
    seat_last[3][3]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[3][3]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s45_stateChanged(int arg1)
{
    if(ui->s45->isChecked()){
    num+=1;
    seat_last[3][4]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[3][4]=0;
    ui->number->setText(QString::number(num));
    }
}



void buy::on_s46_stateChanged(int arg1)
{
    if(ui->s46->isChecked()){
    num+=1;
    seat_last[3][5]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[3][5]=0;
    ui->number->setText(QString::number(num));
    }
}



void buy::on_s51_stateChanged(int arg1)
{
    if(ui->s51->isChecked()){
    num+=1;
    seat_last[4][0]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[4][0]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s52_stateChanged(int arg1)
{
    if(ui->s52->isChecked()){
    num+=1;
    seat_last[4][1]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[4][1]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s53_stateChanged(int arg1)
{
    if(ui->s53->isChecked()){
    num+=1;
    seat_last[4][2]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[4][2]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s54_stateChanged(int arg1)
{
    if(ui->s54->isChecked()){
    num+=1;
    seat_last[4][3]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[4][3]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s55_stateChanged(int arg1)
{
    if(ui->s55->isChecked()){
    num+=1;
    seat_last[4][4]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[4][4]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_s56_stateChanged(int arg1)
{
    if(ui->s56->isChecked()){
    num+=1;
    seat_last[4][5]=1;
    ui->number->setText(QString::number(num));
    }
    else{
    num-=1;
    seat_last[4][5]=0;
    ui->number->setText(QString::number(num));
    }
}


void buy::on_pay_clicked()//支付
{

    if (Database::connect()) {
        QSqlDatabase db = Database::getDatabase();
        QSqlQuery sql_query(db);
        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                    if(seat_last[i][j]==1){
                    QString sql;
                    sql="INSERT INTO buy (u_id,seat,m_id) VALUES ("+u_id+",'"+QString::number(i)+","+QString::number(j)+"',";
                    sql+=QString::number(movie_select[sel])+")";
                    sql_query.exec(sql);
                    }
            }
        }

        QSqlQuery query;
        query.exec("INSERT INTO orders (u_id, m_id, date, time, seat) "
                   "SELECT buy.u_id, query.m_id, query.date, query.time, buy.seat "
                   "FROM buy JOIN query ON buy.m_id = query.p_id");

        query.exec("UPDATE user SET u_act=u_act+1 WHERE u_id="+user_id+"");

    Database::close();
    }
    QMessageBox::about(this, tr("支付成功"), tr("感谢你的支持！"));
    ui->stack->setCurrentWidget(ui->query_page);
    for(int i=0;i<5;i++){
    for (int j = 0; j < 6; j++) {
        if(seat_last[i][j]==1||seat_init[i][j]==1){
                QString name="s"+QString::number(i+1)+QString::number(j+1);
                QCheckBox* now=ui->stack->findChild<QCheckBox*>(name);
                now->setEnabled(true);
                now->setChecked(false);
            }
        }
    }
    num=0;
    ui->textBrowser_4->clear();
}

