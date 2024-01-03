#include "meowregister.hpp"
#include "ui_meowregister.h"
#include "qmessagebox.h"
#include "meowuser.h"
MeowRegister::MeowRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeowRegister)
{
    ui->setupUi(this);

}

MeowRegister::~MeowRegister()
{
    delete ui;
}

void MeowRegister::on_pushButton_register_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    std::string username = ui->lineEdit_username->text().toStdString();
    std::string password = ui->lineEdit_password->text().toStdString();
    std::string checkPwd = ui->lineEdit_check->text().toStdString();
    if(password!=checkPwd){
        QMessageBox::information(this,"warning!","密码不一致");
        return ;
    }
    if(register_Meow(id,username,password)){
       QMessageBox::information(this,"info","注册成功");
       this->regId =id;
    }else{
       QMessageBox::information(this,"info","注册失败");
    }

}

void MeowRegister::on_pushButton_cancel_clicked()
{
    this->close();
}
