#include "registermeow.h"
#include "ui_registermeow.h"

RegisterMeow::RegisterMeow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterMeow)
{
    ui->setupUi(this);
}

RegisterMeow::~RegisterMeow()
{
    delete ui;
}
