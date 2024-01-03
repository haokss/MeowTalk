#include "meowregister.hpp"
#include "ui_meowregister.h"

MeowRegister::MeowRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Meowregister)
{
    ui->setupUi(this);
}

MeowRegister::~Meowregister()
{
    delete ui;
}
