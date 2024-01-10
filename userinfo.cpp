#include "userinfo.hpp"
#include "ui_userinfo.h"
#include "InitSocket.hpp"
extern ClientSocket CSOCKET;
UserInfo::UserInfo(const MeowUserData& userData,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{

    ui->setupUi(this);
    this->userData = userData;
    QPushButton *btn = ui->pushButton_ava;
    if(userData.sex){
        QIcon icon(":/res/_ava/boy.png");
        btn->setIcon(icon);
        btn->setIconSize(QSize(130,130));
    }else{
        QIcon icon(":/res/_ava/girl.png");
        btn->setIcon(icon);
        btn->setIconSize(QSize(130,130));
    }
    QLabel *label = ui->label_id;
    QString id = QString::fromStdString("id:"+std::to_string(userData.id));
    label->setText(id);
    // 名称
    QLineEdit *lineName = ui->lineEdit_name;
    lineName->setText(QString::fromStdString(userData.name));
    // 电话
    QLineEdit *lineTele = ui->lineEdit_tele;
    lineTele->setText(QString::fromStdString(userData.telephone));
    // 签名
    QLineEdit *lineSign = ui->lineEdit_sign;
    lineSign->setText(QString::fromStdString(userData.sign));
    // 性别
    QComboBox *comboBox = ui->comboBox;
    if(userData.sex)
        comboBox->setCurrentIndex(1);
    else
        comboBox->setCurrentIndex(0);

}

UserInfo::~UserInfo()
{
    delete ui;
}

void UserInfo::on_pushButton_submit_clicked()
{
    // 获取修改信息
    QLineEdit *lineName = ui->lineEdit_name;
    std::string name = lineName->text().toStdString();
    // 电话
    QLineEdit *lineTele = ui->lineEdit_tele;
    std::string telephone = lineTele->text().toStdString();
    // 签名
    QLineEdit *lineSign = ui->lineEdit_sign;
    std::string sign = lineSign->text().toStdString();
    // 性别
    QComboBox *comboBox = ui->comboBox;
    int sex = comboBox->currentIndex();
    std::string update = "0#6#"+std::to_string(userData.id)+"#0#"+name+"$"+std::to_string(sex)+"$"+telephone+"$"+
            sign;
    CSOCKET.SendeMessages(update.c_str());

}
