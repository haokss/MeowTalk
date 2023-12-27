#include "addnewtalk.h"
#include "ui_addnewtalk.h"
#include "InitSocket.hpp"
#include "meowuser.h"
extern ClientSocket CSOCKET;
extern MeowUser SELFUSER;
AddNewTalk::AddNewTalk(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddNewTalk)
{
    ui->setupUi(this);
    // 搜索信息改变的信号和槽
    connect(ui->lineEdit,SIGNAL(textChanged(const QString&)), this, SLOT(onSearchChanged(const QString&)));
}

AddNewTalk::~AddNewTalk()
{
    delete ui;
}

void AddNewTalk::on_pushButton_clicked()
{
    // 发送添加好友/群请求
    // TODO:: 逻辑上应该先判断是否已经是好友了
    std::string str = "0#4#"+std::to_string(SELFUSER.self.id)
            +"#"+search.toStdString()+"#add";
    CSOCKET.SendeMessages(str.c_str());
    ui->lineEdit->setText("");
}

void AddNewTalk::onSearchChanged(const QString &newText)
{
    search = newText;
}
