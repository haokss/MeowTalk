#include "delfriend.h"
#include "ui_delfriend.h"
#include "InitSocket.hpp"
#include "meowuser.h"
extern ClientSocket CSOCKET;
extern MeowUser SELFUSER;
DelFriend::DelFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelFriend)
{
    ui->setupUi(this);
}

DelFriend::~DelFriend()
{
    delete ui;
}

void DelFriend::on_pushButton_clicked()
{
    std::string del = ui->lineEdit->text().toStdString();
    std::string delFriend = "0#5#"+std::to_string(SELFUSER.self.id)+"#0#"+del;
    CSOCKET.SendeMessages(delFriend.c_str());
}
