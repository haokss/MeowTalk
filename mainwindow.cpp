#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "usermain.h"
#include "meowregister.hpp"
#include "avabutton.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("萌T聊天");
    this->setWindowFlags(Qt::FramelessWindowHint);    //取消窗体的标题栏
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_main_login_clicked()
{
    // 获取用户的登录信息
    int user_id = this->ui->lineEdit_id->text().toInt();
    std::string password = this->ui->lineEdit_password->text().toStdString();
    // 判断登录信息
    if(login_Meow(user_id,password)==true){
        this->close();
        UserMain *usermain = new UserMain;
        usermain->show();
    }else{
        QMessageBox::information(this,"登陆失败","密码错误");
    }
}

void MainWindow::on_pushButton_exit_clicked()
{
     this->close();
}

void MainWindow::on_pushButton_clicked()
{
    MeowRegister *meowReg = new MeowRegister;
    meowReg->show();
}
