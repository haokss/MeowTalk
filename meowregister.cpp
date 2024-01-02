#include "meowregister.hpp"
#include "ui_meowregister.h"

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
