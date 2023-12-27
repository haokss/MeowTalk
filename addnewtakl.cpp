#include "addnewtakl.h"
#include "ui_addnewtakl.h"

AddNewTakl::AddNewTakl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddNewTakl)
{
    ui->setupUi(this);
}

AddNewTakl::~AddNewTakl()
{
    delete ui;
}
