#include "meowrigister.hpp"
#include "ui_meowrigister.h"

MeowRigister::MeowRigister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeowRigister)
{
    ui->setupUi(this);
}

MeowRigister::~MeowRigister()
{
    delete ui;
}
