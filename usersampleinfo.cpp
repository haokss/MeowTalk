#include "usersampleinfo.hpp"
#include "ui_usersampleinfo.h"

UserSampleInfo::UserSampleInfo(const MeowUserData& data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSampleInfo)
{
    ui->setupUi(this);
    QLabel *label_name = ui->label_name;
    std::string self_name = "用户名："+data.name;
    label_name->setText(QString::fromStdString(self_name));
    // 加载签名
    QLabel *label_id = ui->label_id;
    std::string self_id= "用户id："+ std::to_string(data.id);
    label_id->setText(QString::fromStdString(self_id));
    // 加载签名
    QLabel *label_sign = ui->label_sign;
    std::string self_sign= "签名："+ data.sign;
    label_sign->setText(QString::fromStdString(self_sign));
}

UserSampleInfo::~UserSampleInfo()
{
    delete ui;
}
