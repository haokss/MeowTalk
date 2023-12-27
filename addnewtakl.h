#ifndef ADDNEWTAKL_H
#define ADDNEWTAKL_H

#include <QMainWindow>

namespace Ui {
class AddNewTakl;
}

class AddNewTakl : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNewTakl(QWidget *parent = nullptr);
    ~AddNewTakl();

private:
    Ui::AddNewTakl *ui;
};

#endif // ADDNEWTAKL_H
